CC=gcc 
CFLAGS=-Wall -fno-stack-protector -z execstack -no-pie -m32 -O0 -g

main:
	$(CC) $(CFLAGS) -o vuln vuln.c
	chmod 6755 vuln
