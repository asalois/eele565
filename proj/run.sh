#!/bin/bash
# script to compile and run proj
gcc -o runMain main.c -lm -Wall
(time ./runMain) > out.txt 2>&1
#cat out.txt
#./find_errs.sh
