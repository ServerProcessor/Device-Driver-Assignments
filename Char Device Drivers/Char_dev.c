#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h> /* For the character driver support */

/* ssize is not mentioned in the C standard but in POSIX standard which allows you to be
pretty sure to be able to port them easily among a large family of Unix derivatives (including Linux, but not limited to it) */

/*There's no guarantee in the C or POSIX standards that sizeof(int) >= sizeof(ssize_t), nor the other way around. 
Typically ssize_t is larger than int*/

ssize_t ex07_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
  printk(KERN_ALERT "Inside function %s\n", __FUNCTION__);
  return 0;
}
ssize_t ex07_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
  printk(KERN_ALERT "Inside function %s\n", __FUNCTION__);
  return length;
}
int ex07_close(struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "Inside function %s\n", __FUNCTION__);
  return 0;
}
int ex07_open(struct inode *pinode, struct file *pfile)
{
  printk(KERN_ALERT "Inside function %s\n", __FUNCTION__);
  return 0;
}/* Function pointers are registered */

/* To hold the file operations performed on this device */
struct file_operations ex07_file_operations = {
      .owner = THIS_MODULE,
      .open =  ex07_open,
      .read =  ex07_read,
      .write = ex07_write,
      .release = ex07_close,
};

int ex07_module_init(void)
 {
    printk(KERN_ALERT "Inside function %s\n", __FUNCTION__);
    
    /* Register with the kernel and indicate that we are registering a char device driver */
    /* register_chrdev — Register a major number for character devices.  If major == 0 this functions will dynamically allocate a
       major and return its number. If major > 0 this function will attempt to reserve a device with the given major number and
       will return zero on success. Returns a -ve errno on failure. The name of this device has nothing to do with the name of
       the device in /dev. It only helps to keep track of the different owners of devices. If your module name has only one type
       of devices it's ok to use e.g. the name of the module here. */

    register_chrdev(240 /* Major Number */,
                    "Simple Char Drv" /* Name of the driver */,
                    &ex07_file_operations/* File Operations */);
    return 0;
 }
 
void ex07_module_exit(void)
 {
    printk(KERN_ALERT "Inside function %s\n", __FUNCTION__);
    /* Unregister the char device driver */
    unregister_chrdev(240, "Simple Char Drv");
 }
 
module_init(ex07_module_init);
module_exit(ex07_module_exit);


