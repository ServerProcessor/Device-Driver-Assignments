nano Makefile
obj-m := hello-1.o
sudo make -C /lib/modules/$(uname -r)/build M=$PWD modules
sudo insmod hello-1.ko
