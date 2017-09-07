#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
#include<linux/device.h>//device_create  和  class_creat头文件存放的地方

volatile unsigned long *GPGCON;
volatile unsigned long *GPGDAT;

int key_open (struct inode *node, struct file *file)
{
	*GPGCON &= ~((0x3<<(0*2)) | (0x3<<(3*2)) | (0x3<<(5*2)) | (0x3<<(6*2)) | (0x3<<(7*2)) | (0x3<<(11*2)));
	
	return 0;
}

ssize_t key_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	unsigned char key_vals[6];
	int regval;
	
	if (size != sizeof(key_vals))
		return -EINVAL;
	
	regval = *GPGDAT;
	
	key_vals[0] = (regval & (1<<0)) ? 1 : 0;
	key_vals[1] = (regval & (1<<3)) ? 1 : 0;
	key_vals[2] = (regval & (1<<5)) ? 1 : 0;
	key_vals[3] = (regval & (1<<6)) ? 1 : 0;
	key_vals[4] = (regval & (1<<7)) ? 1 : 0;
	key_vals[5] = (regval & (1<<11)) ? 1 : 0;
	
	copy_to_user(buf , key_vals , sizeof(key_vals));
	
	return sizeof(key_vals);
}

struct file_operations first_fops =
{
	.owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   key_open,     
	.read  =  key_read,
};

int major;
struct class *key_class;
struct class_device *key_device;

int first_drv_init()
{
	major = register_chrdev(0 ,"key", &first_fops);
	
	key_class = class_create(THIS_MODULE , "key");
	

	key_device = device_create(key_class , NULL , MKDEV(major,0) , NULL , "key" );
	
	GPGCON = (volatile unsigned long *)ioremap(0x56000060,16);
	GPGDAT = GPGCON + 1;
	
	printk("major = %d\n",major);
	return 0;
}
void first_drv_exit()
{
	unregister_chrdev(major,"key");
	
	device_unregister(key_device);

	class_destroy(key_class);
}

module_init(first_drv_init);
module_exit(first_drv_exit);

MODULE_LICENSE("GPL");