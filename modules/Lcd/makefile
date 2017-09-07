obj-m := Lcd.o
KDIR :=/linux-2.6.32.2/
all:
	make -C $(KDIR) M=$(PWD) modules CROSS_COMPILE=arm-linux- ARCH=arm
clean:
	rm -rf *.symvers *.ko *.mod.o *.order *.mod.c *.o

