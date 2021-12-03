#!/bin/bash
# script to compile and run proj
gcc -pthread -o runParMain par_main.c -lm -Wall
(time ./runParMain) > out.txt 2>&1
#cat out.txt
#./find_errs.sh
