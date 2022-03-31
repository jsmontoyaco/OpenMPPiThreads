#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <sys/time.h>

#define ITERATIONS 2e9
#define THREADS 16
int range = ITERATIONS/THREADS;


void Pileibnitz(double *picalc, int thread_num){
    int init = range * thread_num;
    int end = range * (thread_num+1);
    for (int i=init; i<end;i++){
        *(picalc+thread_num) += (double) (4.0/(i*2+1));
        i++;
        *(picalc+thread_num) -= (double) (4.0/(i*2+1));
    }
    //printf("\nRange of thread %i begin in %i and ends at %i\n", thread_num, init, end);
}

void main(){
    FILE *fo;
    fo = fopen ("PiOPMINTELU.txt", "a");
    double pi[THREADS];
    struct timeval tval_before, tval_after, tval_result;
    gettimeofday(&tval_before, NULL);

    for(int i=0; i<THREADS; i++){
        pi[i]=0;
    }


    #pragma omp parallel num_threads(THREADS)
    {
        int ID = omp_get_thread_num();
        Pileibnitz(pi, ID);
    }
    //printf("\n Thread %i with pi value of %2.12f\n", 0, pi[0]);
    for(int j=1; j<THREADS; j++){
        pi[0] += pi[j];
        //printf("\n Thread %i with pi value of %2.12f\n", j, pi[j]);
    }

    gettimeofday(&tval_after, NULL); 
    timersub(&tval_after, &tval_before, &tval_result);
    long int seconds = (long int)tval_result.tv_sec;
    long int useconds = (long int)tval_result.tv_usec;
    
    fprintf(fo, "%i %ld.%06ld\n", THREADS ,seconds, useconds);
    fclose(fo);

    printf("Pi calculated with %f iteractions \n With a value of %2.12f \n Executed in %ld.%06ld seconds", ITERATIONS, pi[0], seconds, useconds); 
}
