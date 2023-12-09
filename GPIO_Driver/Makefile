KERNEL := /home/cmp408/rpisrc/linux
PWD := $(shell pwd)
obj-m += GPIO_Driver.o

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL) M=$(PWD) modules
clean:
	make -C $(KERNEL) M=$(PWD) clean
#make KERNEL=/home/cmp408/rpisrc/linux CROSS=/home/cmp408/tools/arm-bcm2708/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-

