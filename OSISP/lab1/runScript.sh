#!/bin/bash
PROG_NAME=$1
output=$(i686-w64-mingw32-g++ $PROG_NAME -lgdi32 -luser32 -lkernel32 -lcomctl32 -lm -mwindows)
if [[ $? != 0 ]]; then
    echo -e "Error:\n$output"
else
    wine ./a.exe
fi
