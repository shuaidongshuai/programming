obj-m := test.o
KERNELDIR ?= /usr/src/kernels/2.6.32-279.el6.i686/
PWD := $(shell pwd)
SYMBOL_INC = $(obj)/../include
EXTRA_CFLAGS += -I $(SYMBOL_INC)
KBUILD_EXTRA_SYMBOLS=$(obj)/../print/Module.symvers

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko* *.mod.c .tmp_versions modules.order  Module.symvers

.PHONY: modules modules_install clean
