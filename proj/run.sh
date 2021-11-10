#!/bin/bash
# script to compile and run proj
gcc -o main main.c -lm -Wall
./main > out.txt
#./find_errs.sh
