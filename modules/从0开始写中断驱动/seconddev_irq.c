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

struct class *second_irq_class;
struct class_device *second_irq_class_dev;

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);/*等待队列*/

/* 中断事件标志, 中断服务程序将它置1，second_irq_read将它清0 */
static volatile int ev_press = 0;

static int key_val;

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

	ev_press = 1;                  /* 表示中断发生了 */
    wake_up_interruptible(&button_waitq);   /* 唤醒休眠的进程 */
	
	return IRQ_HANDLED;
}

static int second_irq_open(struct inode *inode, struct file *file)
{
	request_irq(IRQ_EINT8,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K1",&pins_desc[0] );
	request_irq(IRQ_EINT11,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K2",&pins_desc[1] );
	request_irq(IRQ_EINT13,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K3",&pins_desc[2] );
	request_irq(IRQ_EINT14,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K4",&pins_desc[3] );
	

	return 0;
}

ssize_t second_irq_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	if(size!=1)
	return -EINVAL;

	/* 如果没有按键发生，休眠*/
	wait_event_interruptible(button_waitq, ev_press);

	/* 如果有按键发生，返回*/
	copy_to_user(buf,&key_val, size);
	ev_press = 0;
	
	return 0;
}

int second_irq_close (struct inode *inode, struct file *file)
{
	free_irq(IRQ_EINT8, &pins_desc[0] );
	free_irq(IRQ_EINT11,&pins_desc[1] );
	free_irq(IRQ_EINT13,&pins_desc[2] );
	free_irq(IRQ_EINT14,&pins_desc[3] );
	return 0;
}

static struct file_operations second_irq_fops = {  
	.owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */ 
	.open   =   second_irq_open,    
	.read   =  second_irq_read,
	.release =second_irq_close,
};

int major;

int second_irq_init()
{		
	
	major = register_chrdev(0 , "irq",&second_irq_fops );

	second_irq_class = class_create(THIS_MODULE,"irq");
	second_irq_class_dev = device_create(second_irq_class, NULL, MKDEV(major, 0), NULL, "irq_dev"); 
	
	printk("major = %d \n",major);
	
	return 0;
}
void second_irq_exit()
{	
	unregister_chrdev(major,"irq");
	class_destroy(second_irq_class);
	class_destroy(second_irq_class_dev);
}


module_init(second_irq_init);
module_exit(second_irq_exit);

MODULE_LICENSE("GPL");  
