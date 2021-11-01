#include <stdio.h>
#include <stdlib.h>

#define size 104857600

const int M = 4;

int syms[size];
float md[size];
float rx[size];

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

float getBER(){
    int err = 0;
    for(int i=0; i<size; i++){
        err += ((int)rx[i])^syms[i];
    }
    float ber = (float)err / (float)size;
    return ber;
}

int main(){
    makeSeq();
    pamMod();
    pamDemod();
    if(size<33){
        for(int i=0; i<size; i++){ // print all the sequence and pam modded data
            printf("syms[%02d] = %d md[%02d] = %f rx[%02d] = %f \n",i,syms[i],i,md[i],i,rx[i]);
        }
    }
    float BER = getBER();
    printf("BER = %f \n",BER);
    return 0;
}
