#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/poll.h>
#include <linux/irq.h>
#include <asm/irq.h>
#include <linux/interrupt.h>
#include <asm/uaccess.h>
#include <mach/regs-gpio.h>
#include <mach/hardware.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/sched.h>
#include <linux/gpio.h>

struct class *first_itq_class;
struct class_device *first_irq_class_dev;

static irqreturn_t buttons_irq(int irq, void *dev_id)
{
	printk("irq = %d\n",irq);
	return IRQ_HANDLED;
}

static int s3c24xx_leds_open(struct inode *inode, struct file *file)
{
	request_irq(IRQ_EINT8,buttons_irq,IRQ_TYPE_EDGE_BOTH,"s1",1);
	request_irq(IRQ_EINT11,buttons_irq,IRQ_TYPE_EDGE_BOTH,"s2",1);
	request_irq(IRQ_EINT13,buttons_irq,IRQ_TYPE_EDGE_BOTH,"s3",1);
	request_irq(IRQ_EINT14,buttons_irq,IRQ_TYPE_EDGE_BOTH,"s4",1);
	

	return 0;
}

int first_irq_close (struct inode *inode, struct file *file)
{
	free_irq(IRQ_EINT8,  1);
	free_irq(IRQ_EINT11,1);
	free_irq(IRQ_EINT13,1);
	free_irq(IRQ_EINT14,1);
	return 0;
}

static int s3c24xx_leds_ioctl(    struct inode *inode,     struct file *file,     unsigned int cmd,     unsigned long arg)
{   

}

static struct file_operations fourth_led_fops = {  
	.owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */ 
	.open   =   s3c24xx_leds_open,    
	.ioctl  =   s3c24xx_leds_ioctl,
	.release = first_irq_close,
};

int major;
int first_irq_init()
{		
	
	major = register_chrdev(0 , "irq",&fourth_led_fops );

	first_itq_class = class_create(THIS_MODULE,"irq");
	first_irq_class_dev = device_create(first_itq_class, NULL, MKDEV(major, 0), NULL, "irq_dev"); 
	
	printk("major = %d \n",major);
	
	return 0;
}
void first_irq_exit()
{	
	unregister_chrdev(major,"irq");
	class_destroy(first_itq_class);
}


module_init(first_irq_init);
module_exit(first_irq_exit);

MODULE_LICENSE("GPL");  
