#include <stdio.h>
#include <stdlib.h>

#define size 16

const int M = 4;

int syms[size];
float md[size];

int makeSeq(){ // make a sequence of data from 0 to M-1 
    for(int i=0; i<size; i++){
        syms[i] = rand()%M;
    }
    return 0;
}

int pammod(){ // pam mod the data to be [0-1]
    for(int i=0; i<size; i++){
        md[i] =  ((float)syms[i] / (float)(M-1));
    }
    return 0;
} 


int main(){
    makeSeq();
    pammod();
    for(int i=0; i<size; i++){ // print all the sequence and pam modded data
        printf("syms[%02d] = %d md[%02d] = %f\n",i,syms[i],i,md[i]);
    }
    return 0;
}
