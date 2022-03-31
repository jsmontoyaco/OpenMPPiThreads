#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ITERATIONS 2e9

void Pileibnitz(double *pi){
    for (int i=0; i<ITERATIONS;i++){
        *pi += (double) 1.0/(i*2+1)*4.0;
        i++;
        *pi -= (double) 1.0/(i*2+1)*4.0;
    }
}

void main(){
    FILE *fo;
    fo = fopen ("PiOPMINTELU.txt", "a");
    double pi=0.0;
    struct timeval tval_before, tval_after, tval_result;
    gettimeofday(&tval_before, NULL);

    Pileibnitz(&pi);

    gettimeofday(&tval_after, NULL); 
    timersub(&tval_after, &tval_before, &tval_result);
    long int seconds = (long int)tval_result.tv_sec;
    long int useconds = (long int)tval_result.tv_usec;


    fprintf(fo, "1 %ld.%06ld\n", seconds, useconds);
    fclose(fo);

    printf("Pi calculated with %f iteractions \n With a value of %f \n Executed in %ld.%06ld seconds", ITERATIONS, pi, seconds, useconds); //time execution calc command for linux
}
