#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>      /* File operations strucutre for open/close , read/write to device ( includes init.h too ) */
#include <linux/cdev.h>    /* This is a char driver; makes cdev available and register the char device to the kernel */
#include <linux/device.h>  /* Configuraion of the processor and core peripherals */
#include <linux/errno.h>   /* Error Handling */
#include <asm/uaccess.h>   /*copy_to_user; copy_from_user : To map data from userspace to kernel space */
 
#include "query_ioctl.h"   /* Custom inculsion */
 
#define FIRST_MINOR 0
#define MINOR_CNT 1
 
static dev_t dev;           /* dev_t first | first = mkdev(4,40) or dev_t = <4,40> | int maj,min | maj = MAJOR(dev_t); | min = MINOR(dev_t); */
static struct cdev c_dev;   /* struct cdev operations encapsulates the file operations,major & minor number info */
static struct class *cl;
static int status = 1, dignity = 3, ego = 5;
 
static int my_open(struct inode *i, struct file *f)
{
    return 0;
}
static int my_close(struct inode *i, struct file *f)
{
    return 0;
}

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
static int my_ioctl(struct inode *i, struct file *f, unsigned int cmd, unsigned long arg)
#else
static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
#endif
{
    query_arg_t q;   /* Object of this structure */
 
    switch (cmd)
    {
        case QUERY_GET_VARIABLES:
            q.status = status;
            q.dignity = dignity;
            q.ego = ego;
            if (copy_to_user((query_arg_t *)arg, &q, sizeof(query_arg_t)))  /*Take data from kernelspace to userspace */
            {
                return -EACCES;  /* EACCES when one of the directories composing the path is not readable to the program */
            }
            break;
        case QUERY_CLR_VARIABLES:
            status = 0;
            dignity = 0;
            ego = 0;
            break;
        case QUERY_SET_VARIABLES:
            if (copy_from_user(&q, (query_arg_t *)arg, sizeof(query_arg_t)))
            {
                return -EACCES;
            }
            status = q.status;
            dignity = q.dignity;
            ego = q.ego;
            break;
        default:
            return -EINVAL; /* If one of the  parameters is invalid */
    }
 
    return 0;
}
 
/* To hold the file operations performed on this device */
static struct file_operations query_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
    .ioctl = my_ioctl
#else
    .unlocked_ioctl = my_ioctl
#endif
};
 
static int __init query_ioctl_init(void)
{
    int ret;
    struct device *dev_ret;
 
 
    if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "query_ioctl")) < 0)
    {
        return ret;
    }
 
    cdev_init(&c_dev, &query_fops);  /* New mechanism similar to cdev_add */
 
    if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0) /* cdev_add(struct cdev* dev,dev_t num,unsigned int count) */
    {
        return ret;
    }
     
    if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
    {
        cdev_del(&c_dev);       /* Remove char device from the system */
        unregister_chrdev_region(dev, MINOR_CNT);
        return PTR_ERR(cl);  /* Rerieves the negative error number from IS_ERR */
    }
    if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "query"))) /* Tests if the supplied pointer should be considered an error value instead of a valid pointer to data. */
    {
        class_destroy(cl);
        cdev_del(&c_dev);
        unregister_chrdev_region(dev, MINOR_CNT);
        return PTR_ERR(dev_ret);
    }
 
    return 0;
}
 
static void __exit query_ioctl_exit(void)
{
    device_destroy(cl, dev);  /* Removes a device created with device_create */
    class_destroy(cl);        /* Destroy a struct class structure */
    cdev_del(&c_dev);     /* Remove char device from the system */
    unregister_chrdev_region(dev, MINOR_CNT);
}
 
module_init(query_ioctl_init);
module_exit(query_ioctl_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saumitra");
MODULE_DESCRIPTION("Query ioctl() Char Driver");
