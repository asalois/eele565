#include <stdio.h>
#include <stdlib.h>

#define size 1048576 //2^20
//#define size 268435456 //2^28
//#define size 536870912 //2^29
//#define size 1073741824 //2^30

const int M = 4;

int *syms;
float *md;
float *rx;

int makeSeq(){ // make a sequence of data from 0 to M-1 
    for(int i=0; i<size; i++){
        syms[i] = rand()%M;
    }
    return 0;
}

int pamMod(){ // pam mod the data to be [0-1]
    for(int i=0; i<size; i++){
        md[i] =  ((float)syms[i] / (float)(M-1));
    }
    return 0;
} 

int pamDemod(){ // pam demod the data to be [0-1]
    for(int i=0; i<size; i++){
        rx[i] = md[i] * (M-1);
    }
    rx[size-1] = 0;
    rx[size-2] = 0;
    rx[size-3] = 0;
    return 0;
} 

double getBER(){
    int err = 0;
    for(int i=0; i<size; i++){
        err += ((int)rx[i])^syms[i];
    }
    double ber = (float)err / (float)size;
    return ber;
}

int main(){
    syms = malloc(size*sizeof(int));
    md = malloc(size*sizeof(float));
    rx = malloc(size*sizeof(float));
    makeSeq();
    pamMod();
    pamDemod();
    if(size<33){
        for(int i=0; i<size; i++){ // print all the sequence and pam modded data
            printf("syms[%02d] = %d md[%02d] = %f rx[%02d] = %f \n",i,syms[i],i,md[i],i,rx[i]);
        }
    }
    double BER = getBER();
    printf("BER = %f \n",BER);
    return 0;
}
