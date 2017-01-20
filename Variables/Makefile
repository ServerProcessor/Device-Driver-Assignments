nano Makefile
obj-m := var.o
sudo make -C /lib/modules/$(uname -r)/build M=$PWD modules
sudo insmod var.ko
