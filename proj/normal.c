#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define size 1024 //2^10

int syms[size];
double md[size];
double noise[size];
int M = 4;

int makeSeq()
{ // make a sequence of data from 0 to M-1
    for (int i = 0; i < size; i++)
    {
        syms[i] = rand() % M;
    }
    return 0;
}

int pamMod()
{ // pam mod the data to be [0-1]
    for (int i = 0; i < size; i++)
    {
        md[i] = ((double)syms[i] / (double)(M - 1));
    }
    return 0;
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

int makeNoise(double sig)
{ // add gausian noise
    for (int i = 0; i < size; i++)
    {
        noise[i] = randn(0.0, sig);
    }
    return 0;
}

double getSNR()
{ // find snr
    double sumSig = 0;
    double sumN = 0;
    for (int i = 0; i < size; i++)
    {
        sumSig += md[i];
        sumN += noise[i];
    }
    double aveSig = sumSig / size;
    double aveN = sumN / size;
    double sn = fabs(aveSig / aveN);
    double snr = 10 * log10(sn);
    printf("sig = %f, n = %f \n sn = %f, snr = %f dB\n\n", aveSig, aveN, sn, snr);
    return snr;
}

int main()
{
    makeSeq();
    pamMod();
    double sr = 0.0;
    double s[] = {10.0, 1.0, 0.1, 0.01, 0.001, 0.0001, 0.00001};
    for (int i = 0; i < 7; i++)
    {
        makeNoise(s[i]);
        printf("sigma = %f\n", s[i]);
        sr = getSNR();
        //printf("sigma = %f, SNR = %f dB\n", s[i], sr);
    }
    return 0;
}
