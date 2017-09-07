ifeq ($(KERNELRELEASE),)
	KERNELDIR ?= /usr/src/kernels/2.6.32-279.el6.i686/
	PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	rm -rf *.symvers *.ko* *.mod.o *.order *.mod.c *.o
.PHONY: modules modules_install clean
else
	obj-m := hello.o
endif
