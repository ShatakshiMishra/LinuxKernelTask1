#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
static int load_init(void)
{
        printk(KERN_ALERT "LOAD");
        retun 0;
}
static void load_exit(void)
{
        printk(KERN_ALERT "UNLOAD");
}
module_init(load_init);
module_exit(load_exit);

