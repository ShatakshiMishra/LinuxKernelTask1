#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/init.h>
#define TOUT 10000

static struct task_struct *spare;
static struct timer_list time_ex;


void timer_callback(struct timer_list *time)
{
	printk(KERN_ALERT "Value of jiffie is : %lu\n", jiffies);
	mod_timer(&time_ex,msecs_to_jiffies(TOUT));
}

int do_func(void *p)
{
	while(!kthread_should_stop())
  {
		printk(KERN_ALERT "Inside kernel thread");
		msleep(5000);	
	}
	return 0;
}


static int jiffies_init(void)
{
	printk(KERN_ALERT "Jiffie : %lu\n", jiffies);
	spare = kthread_run(do_func, NULL, "Thread");
	timer_setup(&time_ex, timer_callback, 0);
	mod_timer(&time_ex, jiffies+ msecs_to_jiffies(TOUT));
	return 0;
}


static void jiffies_exit(void)
{
	kthread_stop(spare);
	del_timer(&time_ex);
	printk(KERN_ALERT "jiffies exiting\n");
}


module_init(jiffies_init);
module_exit(jiffies_exit);
