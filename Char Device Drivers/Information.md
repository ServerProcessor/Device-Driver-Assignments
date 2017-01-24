cat /proc/devices : To check for Major Numbers
sudo mknod -m 666 /dev/gg c 240 c : Make Node and everybody gets read write access
ls -l /dev/gg
cat /dev/gg : Read and close
