#include <stdio.h>
#include <stdlib.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <time.h>
#include <sys/wait.h>
#include <omp.h>

#define RT_NICE 441

int main(int argc, char **argv)
{
    double start_time = omp_get_wtime();
    int srt;
    if(argc == 1)
        srt = 0;
    else
        srt = atoi(argv[1]);
    syscall(RT_NICE, (long)getpid(), srt);
    long long int sum = 0;
    for(long i = 0; i < 2000000000; i++)
    {
        sum++;
    }
    double time = omp_get_wtime() - start_time;
    printf("rt_nice: %d sum = %lld time: %f seconds\n", srt, sum, time);
    return 0;
}