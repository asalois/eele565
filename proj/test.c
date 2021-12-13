#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

struct thread_data
{
    int num;
    int que[14];
};

void print_que(void *data)
{
    struct thread_data *t_data;
    t_data = (struct thread_data *)data;
    for (int l = 0; l < t_data->num; l++)
    {
        printf("l= %02d que[%02d]= %02d\n", l, l, t_data->que[l]);
    }
}

int main(int argc, char *argv[])
{
    int num_threads = atoi(argv[1]);
    struct thread_data array[num_threads];
    int snr_num = 14;
    int i, idx;
    if (num_threads > 14 || num_threads < 1)
    {
        
    }
    else
    {

        for (i = 0; i < num_threads; i++)
        {
            array[i].num = 0;
        }
        for (i = 0; i < snr_num; i++)
        { // init struct array
            idx = i % num_threads;
            array[idx].que[array[idx].num] = i;
            array[idx].num += 1;
        }
        for (i = 0; i < num_threads; i++)
        {
            printf("%02d\n", i);
            print_que(&array[i]);
        }
    }

    return 0;
}
