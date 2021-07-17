#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

int driver_open (struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "OPENED");
  return 0;
}
ssize_t driver_read (struct file *pfile, char __user *buff, size_t len, loff_t *offset)
{
   printk(KERN_ALERT "READED");
  return 0;
}
ssize_t driver_write (struct file *pfile, const char __user *buff, size_t len, loff_t *offset)
{
   printk(KERN_ALERT "WRITTEN");
  return len;
 
}
int driver_close (struct inode *pinode, struct file *pfile)
{
   printk(KERN_ALERT "CLOSED");
  return 0;
}
struct file_operations file_opts=
{  .owner= THIS_MODULE,
  .open= driver_open,
  .read= driver_read,
  .write= driver_write,
 .release= driver_close,  
};


static int driver_init(void)
{
        register_chrdev(200,"mydriver",&file_opst);
        return 0;
}
static void driver_exit(void)
{
        unregister_chrdev(200,"mydriver");

}
module_init(driver_init);
module_exit(driver_exit);
