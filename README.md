# Simple Shell Project - ZSH (Zechariah SHell)
Simple shell is a user-mode program that implements the command line interface for Linux/UNIX systems. The program is expected to:
- print a prompt
- read a line
- parse a command, and
- execute a command.

## Compilation
Zsh will be compiled this way:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```