#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define DRIVER_AUTHOR "Saumitra Kapoor <Saumitra.co>"
#define DRIVER_DESC "A driver"

static int hey_init(void)
  {
    printk(KERN_INFO "Can we say anything apart from hey ? \n");
    return 0;
  }

static void hey_exit(void)
  {
    printk(KERN_INFO " You are so cruel \n");
  }

module_init(hey_init);
module_exit(hey_exit);

MODULE_LICENSE("GPL"); /* If not mentioned, certain functionalities will be disabled */
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("Test");
