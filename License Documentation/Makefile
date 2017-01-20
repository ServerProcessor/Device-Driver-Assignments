nano Makefile
obj-m := LD.o
sudo make -C /lib/modules/$(uname -r)/build M=$PWD modules
sudo insmod LD.ko
