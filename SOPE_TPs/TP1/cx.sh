#!/bin/bash

# echo "First arg: $1" # $1 -> First argument
fName="$1.c"
# echo "${fName}"

rm -f *.out # -f to --force and never prompts when .o doesn't exist.

gcc -Wno-error $1 -o "MyProg.out" # $ gcc [programName].c -o programName -- Generates an a.out file.

if [ $? -eq 1 ]
then
    echo "COMPILATION ERROR"
    rm -f *.out
fi