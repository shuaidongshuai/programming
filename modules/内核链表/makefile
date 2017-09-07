obj-m := mylist.o
KDIR := /linux-2.6.32.2_mini/
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux- ARCH=arm
clean:
	rm -rf *.symvers mylist.ko mylist.mod.o modules.order mylist.mod.c mylist.o
