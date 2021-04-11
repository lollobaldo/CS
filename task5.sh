#!/usr/bin/env bash
echo -n '{"command": "GET", "name": "ExamSolutions.pdf", "length": 100, "offset": -89}' | nc localhost 4040
