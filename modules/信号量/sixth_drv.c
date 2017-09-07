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
#include <linux/poll.h>

struct class *sixth_drv_class;
struct class_device *sixth_drv_class_device;

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);
static DECLARE_MUTEX(button_lock);//定义互斥锁
static volatile int ev_press = 0;
static struct fasync_struct *button_async;
static unsigned char key_val;

struct pin_desc{
	unsigned int pin;
	unsigned int key_val;
};

struct pin_desc pins_desc[4] = {
	{S3C2410_GPG(0),0x1},
	{S3C2410_GPG(3),0x2},
	{S3C2410_GPG(5),0x3},
	{S3C2410_GPG(6),0x4},
};

static irqreturn_t buttons_irq(int irq, void *dev_id)
{
	struct pin_desc *pindesc = (struct pin_desc *)dev_id;
	unsigned int pinval = 0;
	
	pinval = s3c2410_gpio_getpin(pindesc->pin);

	if(pinval)
	{
		/* 松开*/
		key_val = 0x80 | pindesc->key_val;		/* 当松开的时候设置键值为0x81*/
	}
	else
	{
		/* 按下*/
		key_val = pindesc->key_val;			/* 当按下的时候设置键值为0x01*/
	}
	
	kill_fasync(&button_async,SIGIO,POLL_IN);//当有按键被按下时驱动程序通知应用程序	(告诉应用程序)
	return IRQ_HANDLED;
}

static int sixth_irq_open(struct inode *inode, struct file *file)
{
	down(&button_lock);
	
	request_irq(IRQ_EINT8,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K1",&pins_desc[0] );
	request_irq(IRQ_EINT11,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K2",&pins_desc[1] );
	request_irq(IRQ_EINT13,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K3",&pins_desc[2] );
	request_irq(IRQ_EINT14,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K4",&pins_desc[3] );
	
	return 0;
}

int sixth_irq_close(struct inode *inode, struct file *file)
{
	up(&button_lock);//释放信号量
	
	free_irq(IRQ_EINT8, &pins_desc[0] );
	free_irq(IRQ_EINT11,&pins_desc[1] );
	free_irq(IRQ_EINT13,&pins_desc[2] );
	free_irq(IRQ_EINT14,&pins_desc[3] );
}

ssize_t sixth_irq_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	if(size!=1)
	return -EINVAL;

	copy_to_user(buf,&key_val, size);
	
	return 0;
}

int sixth_irq_fasync(int fd, struct file *file, int on)
{
	printk("driver: sixth_drv_fasync\n");
	return fasync_helper(fd, file, on, &button_async);
}

struct file_operations sixth_drv_fops = {
	.owner 		=  	THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */ 
	.open 		=   sixth_irq_open,    
	.release	=	sixth_irq_close,
	.read 		=  	sixth_irq_read,
	.fasync		= 	sixth_irq_fasync,
};

int major;
int sixth_drv_init()
{
	major = register_chrdev( 0, "KEY_irq", &sixth_drv_fops);

	sixth_drv_class = class_create(THIS_MODULE,"irq");
	sixth_drv_class_device = device_create(sixth_drv_class,NULL,MKDEV(major, 0),NULL,"irq");

	printk("major = %d\n",major);
	return 0;
}
void sixth_drv_exit()
{
	unregister_chrdev(major,"irq");
	class_destroy(sixth_drv_class);
	device_unregister(sixth_drv_class_device);
}


module_init(sixth_drv_init);
module_exit(sixth_drv_exit);

MODULE_LICENSE("GPL");
