#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

//#define size 64 //2^6
//#define size 128 //2^7
#define size 1024 //2^10
//#define size 4096 //2^12
//#define size 1048576 //2^20
//#define size 2097252 //2^21
//#define size 268435456 //2^28
//#define size 536870912 //2^29
//#define size 1073741824 //2^30

struct signal
{
    int sym[size];
    double mod[size];
    double noise[size];
    double rx[size];
};

const int M = 4;
const int runNum = 16;

struct signal makeSeq(struct signal sig)
{ // make a sequence of data from 0 to M-1
    for (int i = 0; i < size; i++)
    {
        sig.sym[i] = rand() % M;
    }
    return sig;
}

struct signal pamMod(struct signal sig)
{ // pam mod the data to be [0-1]
    for (int i = 0; i < size; i++)
    {
        sig.mod[i] = ((double)sig.sym[i] / (double)(M - 1));
    }
    return sig;
}

double randn(double mu, double sigma)
{
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

struct signal makeNoise(struct signal sig, double sigma)
{ // add gausian noise
    for (int i = 0; i < size; i++)
    {
        sig.noise[i] = randn(0.0, sigma);
    }
    return sig;
}

struct signal pamDemod(struct signal sig)
{ // pam demod the data to be [0, M-1]
    for (int i = 0; i < size; i++)
    {
        sig.rx[i] = (sig.mod[i] + sig.noise[i]) * (double)(M - 1);
    }
    return sig;
}

uint64_t getErr(struct signal sig, uint64_t prevErrs)
{
    uint64_t err = prevErrs;
    for (int i = 0; i < size; i++)
    {
        uint8_t xored = ((uint8_t)round(sig.rx[i])) ^ (uint8_t)sig.sym[i];
        // Iterate through all the bits
        while (xored > 0)
        {
            // If current bit is 1
            if (xored & 1)
            {
                err++;
            }

            xored = xored >> 1;
        }
    }
    return err;
}

double getSNR(struct signal sig)
{ // find snr
    double sumSig = 0;
    double sumN = 0;
    for (int i = 0; i < size; i++)
    {
        sumSig += sig.mod[i];
        sumN += sig.noise[i];
    }
    double aveSig = sumSig / size;
    double aveN = sumN / size;
    double sn = fabs(aveSig / aveN);
    double snr = 10 * log10(sn);
    return snr;
}

int main()
{
    uint64_t err = 0;
    struct signal sig;
    for (int i = 0; i < runNum; i++)
    {
        sig = makeSeq(sig);
        sig = pamMod(sig);
        sig = makeNoise(sig, 0.08);
        sig = pamDemod(sig);
        err += getErr(sig, err);
    }
    double snr = getSNR(sig);
    int total = size * runNum;
    int bottom = total * 8;
    double BER = (double)err / (double)bottom;
    printf("errs = %d \nTotalSims = %d \nTotalBits = %d\n", err, total, bottom);
    printf("BER = %f at %f dB SNR\n", BER, snr);

    return 0;
}
