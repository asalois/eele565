#!/bin/bash
# script to compile and run proj
gcc -lm -Wall -pthread -pg -o par_main.o  pout_main.c
for i in {1..14}
do
    ./par_main.o $i
done
#./par_main.o 1
#gprof par_main.o gmon.out > 1t_prof.txt
#./par_main.o 2
#gprof par_main.o gmon.out > 2t_prof.txt
#./par_main.o 4
#gprof par_main.o gmon.out > 4t_prof.txt
#./par_main.o 8
#gprof par_main.o gmon.out > 8t_prof.txt
#(time ./par_main.o) > out.txt 2>&1
