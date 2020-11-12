#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include "rt_nice.c"

int main(int argc, char **argv)
{
    double start_time = omp_get_wtime();
    int srt;
    if(argc == 1)
        srt = 0;
    else
        srt = atoi(argv[1]);

    int res = rt_nice(getpid(), srt);
    if(res != 0) return -1;

    long long int sum = 0;
    for(long i = 0; i < 2000000000; i++)
    {
        sum++;
    }
    double time = omp_get_wtime() - start_time;
    printf("rt_nice: %d sum = %lld time: %fs\n", srt, sum, time);
    return 0;
}