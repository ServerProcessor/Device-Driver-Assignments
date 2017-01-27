#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>      /* File operations strucutre for open/close , read/write to device ( includes init.h too ) */
#include <linux/cdev.h>    /* This is a char driver; makes cdev available and register the char device to the kernel */
#include <linux/semaphore.h>  /* For multiple threads running at the same time */
#include <asm/uaccess.h>   /*copy_to_user; copy_from_user : To map data from userspace to kernel space */

/* Structure for fake device */
struct fake_device {
  char data[100];
  struct semaphore sem;   /* Prevent corruption from multiple threads running at same time */
} virtual_device;

/* Register the device using cdev object and other variables */
struct cdev *mcdev;  /* m = my */
int major_number;    /* Major number from dev_t */
int ret;             /* To hold return values of functions ( declaring lots of variables will eat up the kernel stack )

dev_t dev_num        /* dev_t first | first = mkdev(4,40) or dev_t = <4,40> | int maj,min | maj = MAJOR(dev_t); | min = MINOR(dev_t); */

#define DEVICE_NAME   "adevice"

/* Register the capabilities of the device by entry module */

static int driver_entry(void) {
    ret = alloc_chrdev_region(&dev_num,0,1,DEVICE_NAME);
    /*  &dev_num is going to hold the major and the minor number
        Start with major number 0 and end with minor number 1 with the device name */
    if(ret<0) {
          printk(KERN_INFO "Failed to allocate a major number");
          return ret; /* Going to return a negative number in case of error */
     }
     
     major_number = MAJOR(dev_num);
     printk(KERN_INFO " Major Number is %d",major_number);
     printk(KERN_INFO "\tuse \"mknod /dev/%s %d 0\" for device file,DEVICE_NAME,major_number);
     
     return 0;
   


