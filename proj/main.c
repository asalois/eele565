#include <stdio.h>
#include <stdlib.h>

#define size 16

const int M = 4;

int syms[size];
float md[size];

int makeSeq(){
    for(int i=0; i<size; i++){
        syms[i] = rand()%M;
    }
    return 0;
}

int pam(){
    for(int i=0; i<size; i++){
        md[i] =  1.0;
    }
    return 0;
} 

int main(){
    makeSeq();
    pam();
    for(int i=0; i<size; i++){
        printf("syms[%02d] = %d md[%02d] = %d\n",i,syms[i],i,md[i]);
    }
    return 0;
}
