EXTRA_CFLAGS = -I $(src)/KernelModulesSDC/

obj-m += drv.o device1.o



all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules 
#gcc device1.c -I/usr/src/linux-headers-5.8.0-53-generic/include/ -o device1

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

