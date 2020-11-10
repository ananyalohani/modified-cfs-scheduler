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

long long int loop()
{
	long long int n = 1000000;
	long long int sum = 0;
	for(int i = 0; i < n; i++)
	{
		sum++;
	}
	return sum;
}

int main(int argc, char **argv)
{
    double start_time = omp_get_wtime();
	long long int sum = 0;
	int srt = 200;
	pid_t pid = fork();

    if(pid != 0)
    {
        syscall(RT_NICE, (long)getpid(), srt);
    }

	if(pid == 0){
		sum = loop();
		double time = omp_get_wtime() - start_time;
		printf("Child Process PID: %ld, rt_nice = 0, time: %f seconds\n", (long)getpid(), time);
	}
	else{
		sum = loop();
		double time = omp_get_wtime() - start_time;
		printf("Parent Process PID: %ld, rt_nice = %d, time: %f seconds\n", (long)getpid(), srt, time);
		wait(NULL);
	}

    return 0;
}