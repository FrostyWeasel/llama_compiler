#!/bin/bash

./compiler < $1 > a.ll
llc -o a.s a.ll
clang++ -O0 -c -o a.o a.s
clang++ -O0 -g -o a.out a.o ./lib/lib.a
