#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include<linux/device.h>//device_create  和  class_creat头文件存放的地方

static struct class *leds_class;
static struct class_device	*leds_class_devs[4];

#define DEVICE_NAME     "led"

static unsigned long *GPBCON;
static unsigned long *GPBDAT;
int major;

int s3c24xx_leds_open(struct inode *inode, struct file *file)
{
    GPBCON = ioremap(0x56000010, 4);
	GPBDAT = GPBCON + 1 ;
	
	*GPBCON = 1<<10 | 1<<12 | 1<<14 | 1<<16;
    return 0;
}

int s3c24xx_leds_ioctl(struct inode *node, struct file *file, unsigned int cmd, unsigned long arg)
{
	
	if(cmd==0)
	{
		*GPBDAT &= ~(1<<( 4 + arg ));
	}
	if(cmd==1)
	{
		*GPBDAT |= 1<<( 4 + arg );
	}
	return 0;
}

struct file_operations s3c24xx_leds_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   s3c24xx_leds_open,     
	.ioctl  =  s3c24xx_leds_ioctl,
};

int third_drv_init(void)
{
	int minor;

    major = register_chrdev(0, DEVICE_NAME, &s3c24xx_leds_fops);

	leds_class = class_create(THIS_MODULE, DEVICE_NAME);
	
	for (minor = 0; minor < 4; minor++)
	leds_class_devs[minor] = device_create(leds_class, NULL, MKDEV(major, minor), NULL, "led%d", minor+1);
        
    printk(DEVICE_NAME " initialized\n");
	
    return 0;
}

void third_drv_exit(void)
{
	int minor;
    /* 卸载驱动程序 */
    unregister_chrdev(major, DEVICE_NAME);

	for (minor = 0; minor < 4; minor++)
	device_unregister(leds_class_devs[minor]);
	
	class_destroy(leds_class);
}

module_init(third_drv_init);
module_exit(third_drv_exit);

MODULE_LICENSE("GPL");