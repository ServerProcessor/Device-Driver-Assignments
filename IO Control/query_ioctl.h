#ifndef QUERY_IOCTL_H   /* If not define, then define. A command to a compiler */
#define QUERY_IOCTL_H
#include <linux/ioctl.h>
 
typedef struct
{
    int status, dignity, ego;
} query_arg_t;  /* Alias name for struct {..} */
 
#define QUERY_GET_VARIABLES _IOR('q', 1, query_arg_t *)  /* Kernel to User */
#define QUERY_CLR_VARIABLES _IO('q', 2)   /* No data movement  */
#define QUERY_SET_VARIABLES _IOW('q', 3, query_arg_t *)  /* User to Kernel */
 
#endif
