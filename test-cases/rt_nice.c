#include <linux/kernel.h>
#include <sys/syscall.h>

#define RT_NICE 441

long rt_nice(pid_t pid, int srt)
{
    int res = syscall(RT_NICE, (long)pid, srt);
    if(res != 0)
    {
        perror("Error");
        return -1;
    }
    return 0;
}