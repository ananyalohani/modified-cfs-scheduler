#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <omp.h>
#include <sys/wait.h>
#include <time.h>

#define RT_NICE 441

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
	double start_time;
	double time;
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
			printf("Process %d: %f seconds\n", i + 1, time);
			exit(0);
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

			int res = syscall(RT_NICE, (long)getpid(), srt);
			if(res < 0)
			{
				perror("Error");
				return -1;
			}

			int sum = loop();
			time = omp_get_wtime() - start_time;
			printf("Process %d: %f seconds\n", i + 1, time);
			exit(0);
		}
	}

	for(int i = 0; i < 5; i++)
	{
		wait(NULL);
	}

	return 0;
}