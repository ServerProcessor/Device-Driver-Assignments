nano Makefile
obj-m := cmd.o
sudo make -C /lib/modules/$(uname -r)/build M=$PWD modules
sudo insmod cmd.ko
