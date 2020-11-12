#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/wait.h>
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
	double start_time, time;
	pid_t pid;
	int srt;

	printf("Time taken with rt_nice = 0:\n");
	for(int i = 0; i < 5; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			start_time = omp_get_wtime();
			int sum = loop();
			time = omp_get_wtime() - start_time;
			printf("Process %d, PID: %ld, Time: %fs\n", i + 1, (long)getpid(), time);
			exit(0);
		}
		else if(pid < 0)
		{
			printf("Error in fork.\n");
			exit(1);
		}
	}

	for(int i = 0; i < 5; i++)
	{
		wait(NULL);
	}

	printf("Time taken with rt_nice > 0:\n");
	for(int i = 0; i < 5; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			start_time = omp_get_wtime();
			srt = 10 * (i + 1);

			int res = rt_nice(getpid(), srt);
			if(res != 0) exit(1);

			int sum = loop();
			time = omp_get_wtime() - start_time;
			printf("Process %d, PID: %ld, rt_nice: %d, Time: %fs\n", i + 1, (long)getpid(), srt, time);
			exit(0);
		}
		else if(pid < 0)
		{
			printf("Error in fork.\n");
			exit(1);
		}
	}

	for(int i = 0; i < 5; i++)
	{
		wait(NULL);
	}

	return 0;
}