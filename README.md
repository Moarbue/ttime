# ttime (Terminal Time)
This is a simple clock inside the terminal using ANSI Escape Sequences.

## Getting Started
To build the program simply invoke
```sh
$ make
```
inside a terminal.

## Known issues
If you are on Windows and don't have enabled UTF-8 Encoding run
```sh
$ chcp.com 65001
```
inside your terminal to enable it inside the current instance.
Also you have to use a **TT** (TrueType Font) for correct rendering.
On Linux you shouldn't have any problems since most terminals use UTF-8 Encoding by default.

Tested Windows with Git Bash.