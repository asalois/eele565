#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>

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

#define num_threads 8

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

struct signal makeSeq(struct signal sig)
{ // make a sequence of data from 0 to M-1
    for (int i = 0; i < size; i++)
    {
        sig.sym[i] = rand() % sig.M;
    }
    return sig;
}

struct signal pamMod(struct signal sig)
{ // pam mod the data to be [0,1]
    for (int i = 0; i < size; i++)
    {
        sig.mod[i] = ((double)sig.sym[i] / (double)(sig.M - 1));
    }
    return sig;
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

struct signal makeNoise(struct signal sig)
{ // add gaussian noise
    for (int i = 0; i < size; i++)
    {
        sig.noise[i] = randn(0.0, sig.sigma);
    }
    return sig;
}

struct signal pamDemod(struct signal sig)
{ // pam demod the data to be [0, M-1]
    for (int i = 0; i < size; i++)
    {
        sig.rx[i] = (sig.mod[i] + sig.noise[i]) * (double)(sig.M - 1);
    }
    return sig;
}

uint64_t getErr(struct signal sig)
{
    uint64_t err = 0;
    for (int i = 0; i < size; i++)
    {
        double rx = sig.rx[i];
        int tx = sig.sym[i];
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

void *sim(void *data){
    struct signal sig = (struct signal *) data;
    sig.err = 0;
    for (int i = 0; i < sig.runNum; i++)
    {
        sig = makeSeq(sig);
        sig = pamMod(sig);
        sig = makeNoise(sig);
        sig = pamDemod(sig);
        sig.err += getErr(sig);
    }
}

int main()
{
    pthread_t threads[num_threads];
    int M = 8;
    double var[] = {0.25, 0.1, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.025, 0.02, 0.015, 0.0125, 0.01};
    uint64_t runNum = (uint64_t)pow(2, 10); // the number of simulations to run
    uint64_t total = size * runNum; // the total number of data points
    uint64_t bottom = total * log2(M); // the total number of bits
    if(bottom < 1000001){ 
        printf("nRuns = %lu nPoints = %lu nBits = %lu\n\n", runNum, total, bottom);
    }else{
        printf("nRuns = %.3e nPoints = %.3e nBits = %.3e\n", (double)runNum, (double)total, (double)bottom);
    }
    printf("Size = %d M = %d\n\n", (int)size, M);
    for (int k = 0; k < 14; k++)
    {
        uint64_t err = 0;
        struct signal sig;
        sig.M = M;
        sig.sigma = var[k];
        for (int i = 0; i < num_threads; i++)
        {
            sig.runNum = runNum / num_threads;
            //sig = sim(sig);
            err += sig.err;
            rc = pthread_create(&threads[i], NULL, sim, (void *) &sig);
            if (rc){
                printf("ERROR: return code from pthread_create() is %d\n", rc);
                printf("Code %d= %s\n",rc,strerror(rc));
                exit(-1);
            }
        double snr = getSNR(sig);
        double BER = (double)err / (double)bottom;
        printf("sigma = %f\n", sig.sigma);
        printf("errs = %lu \nBER = %.3g at %2.3f dB SNR\n\n", err, BER, snr);
    }
    return 0;
}
