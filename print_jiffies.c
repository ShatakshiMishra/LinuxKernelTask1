#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/sched.h>
#include<linux/wait.h>
#include<linux/kthread.h>
#include<linux/delay.h>
#include<linux/device.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,11,0)
#include <linux/sched/signal.h>
#endif
int delay=HZ;

static struct task_struct *thread_wait;

static int thread_func(void *wait)
{
        unsigned long j1,j2;
        allow_signal(SIGKILL);
        while(!kthread_should_stop())
        {
        j1=jiffies;
        j2=j1+delay;

        while(time_before(jiffies,j2))
        cpu_relax();
                j2=jiffies;
                printk(KERN_ALERT "jiffies starts = %lu\t and jiffies end=%lu\n",j1,j2);
                if(signal_pending(current))
                break;
        }
                printk(KERN_ALERT "thread is stopped..\n");
                thread_wait=NULL;
                return 0;
}

static int delay_init(void)
{
        printk(KERN_ALERT "Creating thread......\n");
        thread_wait=kthread_run(thread_func,NULL,"mythread");
        return 0;
 }
static void delay_exit(void)
{
        printk(KERN_ALERT "Removing the module...\n");
        if(thread_wait !=NULL)
        {
                kthread_stop(thread_wait);
                printk(KERN_ALERT "stopping the thread...\n");
        }
}

module_init(delay_init);
module_exit(delay_exit);

      
