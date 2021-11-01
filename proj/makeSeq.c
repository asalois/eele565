#include <stdio.h>
#include <stdlib.h>

int makeSeq(int nSyms, int size){
    for(int i=0; i<size;i++){
        syms[i] = rand()%nSyms;
    }
    printf("Done\n");
    return syms;
}