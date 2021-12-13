#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

//#define size 64 //2^6
//#define size 128 //2^7
//#define size 1024 //2^10
//#define size 4096 //2^12
#define size 8192 //2^13
//#define size 16384 //2^14
//#define size 1048576 //2^20
//#define size 2097252 //2^21
//#define size 268435456 //2^28
//#define size 536870912 //2^29
//#define size 1073741824 //2^30

struct signal
{
    int M;
    int runNum;
    double sigma;
    int sym[size];
    double mod[size];
    double noise[size];
    double rx[size];
    uint64_t err;
};

struct thread_data
{
    int num;
    struct signal *que[14]
};

pthread_barrier_t barrier;

void makeSeq(struct signal *sig)
{ // make a sequence of data from 0 to M-1
    for (int i = 0; i < size; i++)
    {
        sig->sym[i] = rand() % sig->M;
    }
}

void pamMod(struct signal *sig)
{ // pam mod the data to be [0,1]
    for (int i = 0; i < size; i++)
    {
        sig->mod[i] = ((double)sig->sym[i] / (double)(sig->M - 1));
    }
}

double randn(double mu, double sigma)
{ // get a random number based on normal distribution
    double U1, U2, W, mult;
    static double X1, X2;
    static int call = 0;

    if (call == 1)
    {
        call = !call;
        return (mu + sigma * (double)X2);
    }

    do
    {
        U1 = -1 + ((double)rand() / RAND_MAX) * 2;
        U2 = -1 + ((double)rand() / RAND_MAX) * 2;
        W = pow(U1, 2) + pow(U2, 2);
    } while (W >= 1 || W == 0);

    mult = sqrt((-2 * log(W)) / W);
    X1 = U1 * mult;
    X2 = U2 * mult;

    call = !call;

    return (mu + sigma * (double)X1);
}

void makeNoise(struct signal *sig)
{ // add gaussian noise
    for (int i = 0; i < size; i++)
    {
        sig->noise[i] = randn(0.0, sig->sigma);
    }
}

void pamDemod(struct signal *sig)
{ // pam demod the data to be [0, M-1]
    for (int i = 0; i < size; i++)
    {
        sig->rx[i] = (sig->mod[i] + sig->noise[i]) * (double)(sig->M - 1);
    }
}

uint64_t getErr(struct signal *sig)
{
    uint64_t err = 0;
    for (int i = 0; i < size; i++)
    {
        double rx = sig->rx[i];
        int tx = sig->sym[i];
        double rnd = round(rx);
        if (rnd < 0)
        {
            rnd = 0;
        }
        uint8_t rxu = (uint8_t)rnd;
        uint8_t txu = (uint8_t)tx;
        uint8_t xored = rxu ^ txu;
        while (xored > 0)
        {
            // If current bit is 1
            if (xored & 1)
            {
                err++;
            }

            xored = xored >> 1;
        }
        //printf("err = %lu\n",err );
    }
    return err;
}

double getSNR(struct signal sig)
{ // find snr
    double sumSig = 0;
    for (int i = 0; i < size; i++)
    {
        sumSig += sig.mod[i];
    }
    double aveSig = sumSig / size;
    double var = sig.sigma * sig.sigma;
    double sn = fabs(aveSig * aveSig / var);
    double snr = 10 * log10(sn);
    return snr;
}

void *Sim(void *data)
{
    struct thread_data *t_data;
    t_data = (struct thread_data *)data;
    for (int l = 0; l < t_data->num; l++)
    {
        struct signal *sig = t_data->que[l];
        makeNoise(sig);
        for (int i = 0; i < sig->runNum; i++)
        {
            makeSeq(sig);
            pamMod(sig);
            pamDemod(sig);
            sig->err += getErr(sig);
        }
    }
    pthread_barrier_wait(&barrier);
}

int main(int argc, char *argv[])
{
    clock_t start = time(NULL);
    int num_threads = atoi(argv[1]);
    int snr_num = 14;
    pthread_t threads[num_threads];
    struct signal signal_array[snr_num];
    struct thread_data data[num_threads];
    int M = 8;
    int rc, i, bar_num;
    double var[] = {0.25, 0.1, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.025, 0.02, 0.015, 0.0125, 0.01};
    uint64_t runNum = (uint64_t)pow(2, 13); // the number of simulations to run
    uint64_t total = size * runNum;         // the total number of data points
    uint64_t bottom = total * log2(M);      // the total number of bits
    for (i = 0; i < snr_num; i++)
    { // init struct array
        signal_array[i].M = M;
        signal_array[i].err = 0;
        signal_array[i].sigma = var[i];
        signal_array[i].runNum = runNum;
        if (num_threads == 1)
        {
            data[0].num = 14;
            data[0].que[i] = &signal_array[i];
        }
        else if (num_threads < 14)
        {
            int idx = (i + 1) % num_threads;
            data[idx].que[i / num_threads] = &signal_array[i];
            if (snr_num % num_threads == 0)
            {
                data[idx].num = snr_num / num_threads;
            }
            else if (idx)
            {
                data[idx].num = snr_num / num_threads;
            }
            else
            {

                data[idx].num = (int)round((double)snr_num / num_threads);
            }
        }
    }
    if (bottom < 1000001)
    {
        printf("nRuns = %lu nPoints = %lu nBits = %lu\n\n", runNum, total, bottom);
    }
    else
    {
        printf("nRuns = %.3e nPoints = %.3e nBits = %.3e\n", (double)runNum, (double)total, (double)bottom);
    }
    printf("Size = %d M = %d threads=%d\n\n", (int)size, M, num_threads);
    pthread_barrier_init(&barrier, NULL, num_threads + 1);
    for (i = 0; i < num_threads; i++)
    {
        rc = pthread_create(&threads[i], NULL, Sim, (void *)&data[i]);
        if (rc)
        {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            printf("Code %d= %s\n", rc, strerror(rc));
            exit(-1);
        }
    }
    pthread_barrier_wait(&barrier);

    for (int i = 0; i < snr_num; i++)
    {
        double snr = getSNR(signal_array[i]);
        double BER = (double)signal_array[i].err / (double)bottom;
        printf("sigma = %f\n", signal_array[i].sigma);
        printf("errs = %lu \nBER = %.3g at %2.3f dB SNR\n\n", signal_array[i].err, BER, snr);
    }
    clock_t stop = time(NULL);
    printf("Elapsed: %d seconds\n\n\n", (stop - start));
    pthread_exit(NULL);
    return 0;
}
