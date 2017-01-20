#include <linux/module.h>  /* Needed by all module */
#include <linux/kernel.h>  /* Needed for kern info */
#include <linux/init.h>    /* Needed for the macros- will be discussed */

static int hey_init(void)
  {
     printk(KERN_INFO "How are You ? \n");
     return 0;  /* Loaded successfully */
  }

static void hey_exit(void)
  {
     printk(KERN_INFO "Okay fine, Bye \n");
  }

module_init(hey_init);
module_exit(hey_exit);
