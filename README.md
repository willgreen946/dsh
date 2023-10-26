# About DSH
DSH is a shell for UNIX and Linux systems, written in C89 for fun, it's IO uses unistd write() and read() and termios raw mode stuff
Right now, I am not aiming for POSIX compliance, as this is just for fun.

# Things to add
- History
- Last command !!
- Pipes

# Bugs
Backspace handling is shotty right now, sometimes it will mess up the string inputted, so look into this (me).
CTRL+C and other things to do with signals don't do anything, not really a bug but something to make something out of
