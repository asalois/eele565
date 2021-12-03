#!/bin/bash
# script to compile and run proj
gcc -pthread -lm -Wall -o hello.o hello32.c &&  time ./hello.o
#(time ./hello.o) > out_hello.txt 2>&1
