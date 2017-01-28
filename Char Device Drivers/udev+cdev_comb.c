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
int ret;             /* To hold return values of functions ( declaring lots of variables will eat up the kernel stack )*/

dev_t dev_num        /* dev_t first | first = mkdev(4,40) or dev_t = <4,40> | int maj,min | maj = MAJOR(dev_t); | min = MINOR(dev_t); */

#define DEVICE_NAME   "adevice"

int device_open(struct inode *inode, struct file *filp){/* *filp contains the file operation structure defined at the bottom */
  /* Only one process to open the device by using semaphore asmutual exclusive lock */
  if(down_interruptible(&virtual_device.sem) != 0) {
    printk(KERN_ALERT "Could not lock device during open");
    return -1;
  }
  
  printk(KERN_INFO "Opened device");
  return 0;
}

ssize_t device_read(struct file *filp, char *bufStoreData, size_t bufCount, loff_t *curOffset) { /*Offset tells current position of open file */
  printk(KERN_INFO "Reading from device");
  ret = copy_to_user(bufStoreData,virtual_device.data,bufCount); /*Take data from kernelspace to userspace */
  /* copy_to_user(destination,source,sizetotransfer); */
}

ssize_t device_write(struct file *filp, const char *bufStoreData, size_t bufCount, loff_t *curOffset) { /*Offset tells current position of open file */
  printk(KERN_INFO "Writing to device");
  ret = copy_to_user(virtual_device.data,bufSourceData, bufCount); /*Take data from kernelspace to userspace */
}

int device_close(struct inode *inode, struct file *filp){/* *filp contains the file operation structure defined at the bottom */
    up(&virtual_device.sem); /*Release of mutex */
    printk(KERN_INFO "Closd device");
    return 0;
  }

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = device_open,
    .release = device_close,
    .write = device_write,
    .read = device_read
};

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
     
     mcdev = cdev_alloc(); /*Create our cdev structure */
     mcdev->ops = &fops;   /* struct file_operations */
     mcdev->owner = THIS_MODULE;
     /* cdev is now created and we need to add it to the kernel */
     ret = cdev_add(mcdev,dev_num,1); /* cdev_add(struct cdev* dev,dev_t num,unsigned int count) */
     if(ret<0) {
       printk(KERN_ALERT "Unable to add cdev to kernel");
       return ret;
     }
     sema_init(&virtual_device.sem,1);    
     return 0;
 }
            
 static void driver_exit(void) {
     cdev_del(mcdev)
     unregister_chrdev_region(dev_num,1);
     pritnk(KERN_ALERT "Unloaded the module");
 }
 
 module_init(driver_entry);
 module_exit(driver_exit);
            
   


