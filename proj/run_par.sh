#!/bin/bash
# script to compile and run proj
gcc -lm -Wall -pthread -o par_main.o  par_main.c
(time ./par_main.o) > out.txt 2>&1
#cat out.txt
#./find_errs.sh
