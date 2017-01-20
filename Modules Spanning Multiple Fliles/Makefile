obj-m += startstop.o
startstop-objs := start.o stop.o


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
  
sudo insmod startstop.ko
