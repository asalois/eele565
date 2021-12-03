#!/bin/bash
# script to compile and run proj
gcc -lm -Wall -o main.o main.c
(time ./main.o) > out.txt 2>&1
#cat out.txt
#./find_errs.sh
