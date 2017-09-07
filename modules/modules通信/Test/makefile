	obj-m :=test.o
	KERNELDIR ?= /root/linux-4.4.5/
	PWD := $(shell pwd)
	SYMBOL_INC =$(obj)/../include/
	EXTRA_CFLAGS += -I $(SYMBOL_INC)
	KBUILD_EXTRA_SYMBOLS=$(boj)/../add_sub/Module.symvers
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	rm -rf *.o *.mod.c *.mod.o *.ko* *.order *.symvers
.PHONY: modules modules_install clean

