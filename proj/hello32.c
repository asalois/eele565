/******************************************************************************
* FILE: hello32.c
* DESCRIPTION:
*   A "hello world" Pthreads program which creates a large number of 
*   threads per process.  A sleep() call is used to insure that all
*   threads are in existence at the same time.  Each Hello thread does some
*   work to demonstrate how the OS scheduler behavior affects thread 
*   completion order.
* AUTHOR: Blaise Barney
* LAST REVISED: 01/29/09
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NTHREADS 64


void *Hello(void *threadid)
{
   int i;
   double result=0.0;
   sleep(1);
   for (int i=0; i<1000000000; i++) {
     result = (double)i*i*i;
     result = result + i;
     }
   printf("%ld: Hello World!\n", threadid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NTHREADS];
int rc; 
long t;
for(t=0;t<NTHREADS;t++){
  rc = pthread_create(&threads[t], NULL, Hello, (void *)t);
  if (rc){
    printf("ERROR: return code from pthread_create() is %d\n", rc);
    printf("Code %d= %s\n",rc,strerror(rc));
    exit(-1);
    }
   }
printf("main(): Created %ld threads.\n", t);
pthread_exit(NULL);
}
