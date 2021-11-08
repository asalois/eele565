#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define size 64 //2^6
//#define size 128 //2^7
//#define size 1024 //2^10
//#define size 4096 //2^12
#define size 1048576 //2^20
//#define size 2097252 //2^21
//#define size 268435456 //2^28
//#define size 536870912 //2^29
//#define size 1073741824 //2^30

const int M = 16;

int *syms;
double *md;
double *rx;
double *noise;

int makeSeq(){ // make a sequence of data from 0 to M-1 
    for(int i=0; i<size; i++){
        syms[i] = rand()%M;
    }
    return 0;
}

int pamMod(){ // pam mod the data to be [0-1]
    for(int i=0; i<size; i++){
        md[i] =  ((double)syms[i] / (double)(M-1));
    }
    return 0;
} 

int pamDemod(){ // pam demod the data to be [0-1]
    for(int i=0; i<size; i++){
        rx[i] = (md[i] + noise[i]) * (double)(M-1);
    }
    return 0;
} 

double getBER(){
    int err = 0;
    for(int i=0; i<size; i++){
        err += ((int)round(rx[i]))^syms[i];
    }
    double ber = (double)err / ((double)size*log2(M)) ;
    return ber;
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
    return snr;
}

int main(){
    syms = malloc(size*sizeof(int));
    md = malloc(size*sizeof(double));
    noise = malloc(size*sizeof(double));
    rx = malloc(size*sizeof(double));
    makeSeq();
    pamMod();
    makeNoise(0.01);
    double snr = getSNR();
    pamDemod();
    double BER = getBER();
    printf("BER = %f at %f dB SNR\n",BER,snr);
    return 0;
}
