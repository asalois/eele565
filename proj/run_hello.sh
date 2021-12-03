#!/bin/bash
# script to compile and run proj
gcc -pthread -lm -Wall -o hello.o hello_arg2.c &&  time ./hello.o
#(time ./hello.o) > out_hello.txt 2>&1
