#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <omp.h>
#include "rt_nice.c"

long long int loop()
{
	long long int n = 2000000000;
	long long int sum = 0;
	for(int i = 0; i < n; i++)
	{
		sum++;
	}
	return sum;
}

int main(int argc, char **argv)
{
	long long int sum = 0;
	int srt;

	if(argc == 1)
        srt = 200;
    else
        srt = atoi(argv[1]);

	pid_t pid = fork();

    if(pid > 0)
    {
        int res = rt_nice(getpid(), srt);
    	if(res != 0) return -1;
    }

	if(pid == 0)
	{
		double start_time = omp_get_wtime();
		sum = loop();
		double time = omp_get_wtime() - start_time;
		printf("Child Process PID: %ld, rt_nice = %d, time: %fs\n", (long)getpid(), 0, time);
	}
	else if(pid > 0)
	{
		double start_time = omp_get_wtime();
		sum = loop();
		double time = omp_get_wtime() - start_time;
		printf("Parent Process PID: %ld, rt_nice = %d, time: %fs\n", (long)getpid(), srt, time);
		wait(NULL);
	}
	else
	{
		fprintf(stderr, "Error in fork.\n");
	}

    return 0;
}