ifneq ($(KERNELRELEASE),)

obj-m:=add,sub.o

else

KDIR:=/lib/modules/4.2.0-22-generic/build
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -f *.ko *.o *.mod.o *.mod.c *.symvers *.order
endif
