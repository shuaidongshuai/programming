ifeq ($(KERNELRELEASE),)
	KERNELDIR ?= /root/linux-4.4.5/
	PWD := $(shell pwd)
	PRINT_INC =$(PWD)/../include
	EXTRA_CFLAGS += -I $(PRINT_INC)
modules:
	$(MAKE) -I $(PRINT_INC) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	rm -rf *.o *.mod.c *.mod.o *.ko* *.order *.symvers
.PHONY: modules modules_install clean
else
	obj-m :=add_sub.o
endif
