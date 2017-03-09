#!/bin/bash 
make clean
make
mknod assign6 c 65 0
chmod a+w assign6
make user
insmod assignment6.ko

