#!/bin/bash
# script to compile and run proj
gcc -o main main.c -lm -Wall
time ./main > out.txt
cat out.txt
#./find_errs.sh
