#!/bin/bash
# script to compile and run proj
gcc -lm -Wall -pthread -o par_main.o  par_main.c
./par_main.o 10
./par_main.o 20
#(time ./par_main.o) > out.txt 2>&1
