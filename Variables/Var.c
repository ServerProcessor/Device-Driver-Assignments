#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int hey_initdata = 3;

static int hey_init(void)
  {
     printk(KERN_INFO "Hey Again Part %d \n", hey_initdata);
     return(0);
  }

static void hey_exit(void)
  {
     printk(KERN_INFO "Bye Again \n");
  }

module_init(hey_init);
module_exit(hey_exit);
