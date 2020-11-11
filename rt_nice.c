SYSCALL_DEFINE2(rt_nice, long, pid, int, rt_nice)
{
    if(rt_nice < 0)
    {
        printk(KERN_ALERT "Invalid value of rt_nice. Provide a non-negative value.\n");
		return -EINVAL;			// invalid argument
    }

    if(pid < 1 || pid > 2147483647)
    {
        printk(KERN_ALERT "Invalid value of PID.\n");
        return -EINVAL;			// invalid argument
    }

    unsigned long long int val = (unsigned long long int)rt_nice * 1000000000;
    struct task_struct *task = pid_task(find_vpid(pid), PIDTYPE_PID);

    if(task == NULL) 
    {
        printk(KERN_ALERT "No such task with PID = %ld\n.", pid);
		return -ESRCH;			// no such process
    }
    struct sched_entity *task_se = &(task->se);
    task_se->rt_nice = val;
    printk(KERN_INFO "rt_nice value modified successfully.\n");
    return 0;
}