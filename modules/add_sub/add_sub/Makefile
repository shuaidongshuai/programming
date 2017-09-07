ifeq ($(KERNELRELEASE),)

    KERNELDIR ?= /usr/src/kernels/2.6.32-279.el6.i686/
    PWD := $(shell pwd)
    PRINT_INC =$(PWD)/../include
    EXTRA_CFLAGS += -I $(PRINT_INC)

modules:
	$(MAKE) -I $(PRINT_INC) -C $(KERNELDIR) M=$(PWD) modules
	echo $(PRINT_INC)

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions modules.order  Module.symvers

.PHONY: modules modules_install clean

else
    # called from kernel build system: just declare what our modules are
    obj-m := add_sub.o 
endif



