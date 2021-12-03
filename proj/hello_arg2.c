/******************************************************************************
* FILE: hello_arg2.c
* DESCRIPTION:
*   A "hello world" Pthreads program which demonstrates another safe way
*   to pass arguments to threads during thread creation.  In this case,
*   a structure is used to pass multiple arguments.
* AUTHOR: Blaise Barney
* LAST REVISED: 01/29/09
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 8

char *messages[NUM_THREADS];

struct thread_data
{
  int thread_id;
  int sum;
  int r_num;
  char *message;
};

struct thread_data thread_data_array[NUM_THREADS];

void *PrintHello(void *threadarg)
{
  int taskid, sum, num;
  char *hello_msg;
  struct thread_data *my_data;

  sleep(2);
  my_data = (struct thread_data *)threadarg;
  taskid = my_data->thread_id;
  sum = my_data->sum;
  hello_msg = my_data->message;
  num = my_data->r_num;
  //num = (double)sum * (rand() % 100) /100;
  num = sum * sum;
  my_data->r_num = num;
  printf("Thread %d: %s  Sum=%d randN=%d\n", taskid, hello_msg, sum, num);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t threads[NUM_THREADS];
  int *taskids[NUM_THREADS];
  int rc, t, sum, sum_sum;

  sum = 0;
  messages[0] = "English: Hello World!";
  messages[1] = "French: Bonjour, le monde!";
  messages[2] = "Spanish: Hola al mundo";
  messages[3] = "Klingon: Nuq neH!";
  messages[4] = "German: Guten Tag, Welt!";
  messages[5] = "Russian: Zdravstvytye, mir!";
  messages[6] = "Japan: Sekai e konnichiwa!";
  messages[7] = "Latin: Orbis, te saluto!";

  for (t = 0; t < NUM_THREADS; t++)
  {
    sum = sum + t;
    thread_data_array[t].thread_id = t;
    thread_data_array[t].sum = sum;
    thread_data_array[t].message = messages[t];
    printf("Creating thread %d\n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello, (void *)&thread_data_array[t]);
    if (rc)
    {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  sleep(5);
  sum_sum = 0;
  for (int i = 0; i < NUM_THREADS; i++)
  {
    sum_sum += thread_data_array[i].r_num;
    printf("%d\n", sum_sum);
  }
  printf("sum of squares is %d\n", sum_sum);

  pthread_exit(NULL);
}
