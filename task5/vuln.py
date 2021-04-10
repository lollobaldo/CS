#!/usr/bin/env python3

import socketserver
import socket
import json
import sys
from json.decoder import JSONDecodeError

class FileRecord:
    start  = 0
    length = 0
    public = False

    def __init__(self, start, length, public=False):
        self.start = start
        self.length = length
        self.public = public
    def __repr__(self):
        return '{{"start":{},"length":{},"public":{}}}'.format(self.start, self.length, self.public)

with open("/task5/files.vault", "rb") as f:
    fileblob = f.read()

fileDirectory = {
        "Hello": FileRecord(0, 10, True),
        "World": FileRecord(5, 5, True),
        "Secret": FileRecord(12, 87, False),
        "ExamSolutions.pdf": FileRecord(100, 64487, True)
        }

class FileServerHandler(socketserver.BaseRequestHandler):
    def handle(self):
        data = self.request.recv(1024).strip()
        try:
            request = json.loads(data.decode())
        except JSONDecodeError:
            self.request.sendall("Failed to decode JSON".encode())
            return

        print("Received request: {}".format(request));

        if request.get("command", None)=="GET":
            name = request.get("name", None)
            length = request.get("length", 0)
            offset = request.get("offset", 0)
            if name in fileDirectory:
                f = fileDirectory[name]
            else:
                self.request.sendall("404".encode())
                return
            print(f) 
            if length > f.length or offset > f.length:
                self.request.sendall("Naughty, naughty!".encode())
                return
            elif not f.public:
                self.request.sendall("The cake is a lie!".encode())
            else:
                print(f.start+offset, f.start+offset+length)
                self.request.sendall(fileblob[f.start+offset:f.start+offset+length])
        elif request.get("command", None) == "LIST":
            self.request.sendall(fileDirectory.__repr__().encode())
        else:
            self.request.sendall("Invalid Command".encode())

# Use systemd provided socket file instead of binding directly.
class Server(socketserver.TCPServer):
    SYSTEMD_FIRST_SOCKET_FD = 3

    def __init__(self, server_address, handler_cls):
        socketserver.TCPServer.__init__(
            self,
            server_address,
            handler_cls,
            bind_and_activate=False)
        self.socket = socket.fromfd(
            self.SYSTEMD_FIRST_SOCKET_FD,
            self.address_family,
            self.socket_type)

if __name__ == "__main__":
    server = Server(("localhost", int(sys.argv[1])), FileServerHandler)
    server.serve_forever()
