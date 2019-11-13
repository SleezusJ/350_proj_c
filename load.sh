#! /bin/bash

bcc -ansi -c -o tstpr1.o tstpr1.c

as86 -o userlib.o userlib.asm

ld86 -d -o tstpr1 tstpr1.o userlib.o

./loadFile tstpr1

echo "done."
