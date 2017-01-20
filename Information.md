Information regarding the files : /proc/modules

A 'kmod' (kernel driver module) is the pre-compiled, low-level software interface between the kernel and a driver. It gets loaded (into RAM) and merged into the running kernel. Linux kmods are specific to one and only one kernel, and will not work (nor even load) for any other kernel.

modinfo pq.ko : To see what kind of information it is.

sudo tail -f /var/log/kern.log

