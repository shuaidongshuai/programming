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
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/sched.h>
#include <linux/gpio.h>

struct class *fourth_irq_class;
struct class_device *fourth_irq_class_dev;

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);/*注册button_waitq 这个等待队列*/

int  s = 0;

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

    wake_up_interruptible(&button_waitq);   /* 唤醒休眠的进程 */
	s = 1;
	return IRQ_HANDLED;
}

static int fourth_irq_open(struct inode *inode, struct file *file)
{
	request_irq(IRQ_EINT8,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K1",&pins_desc[0] );//pins_desc这个结构体将传给buttons_irq第二个参数
	request_irq(IRQ_EINT11,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K2",&pins_desc[1] );
	request_irq(IRQ_EINT13,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K3",&pins_desc[2] );
	request_irq(IRQ_EINT14,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K4",&pins_desc[3] );
	
	return 0;
}

ssize_t fourth_irq_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	if(size!=1)
	return -EINVAL;

	copy_to_user(buf,&key_val, size);
	
	s = 0;
	
	return 0;
}

unsigned int fourth_irq_poll(struct file *file, struct poll_table_struct *wait)
{
	unsigned int mask = 0;
	
	/* 将button_waitq( 等待队列) 放入到poll_table 中去*/
	poll_wait(file,&button_waitq,wait);

	if(s == 1)
	mask |= POLLIN | POLLRDNORM;/*分别是设备可读，数据可读*/
	//返回值是 可读设备的个数    不是很明白 还有待进一步读内核代码
	return mask;
}


int fourth_irq_close (struct inode *inode, struct file *file)
{
	free_irq(IRQ_EINT8, &pins_desc[0] );
	free_irq(IRQ_EINT11,&pins_desc[1] );
	free_irq(IRQ_EINT13,&pins_desc[2] );
	free_irq(IRQ_EINT14,&pins_desc[3] );
	printk("\nhave been closed\n");
	return 0;
}

static struct file_operations fourth_irq_fops = {  
	.owner 	=   	THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */ 
	.open 	=   	fourth_irq_open,    
	.read 	=  		fourth_irq_read,
	.release 	=	fourth_irq_close,
	.poll     	=	fourth_irq_poll,
};

int major;

int fourth_irq_init()
{		
	
	major = register_chrdev(0 , "irq",&fourth_irq_fops );

	fourth_irq_class = class_create(THIS_MODULE,"irq");
	fourth_irq_class_dev = device_create(fourth_irq_class, NULL, MKDEV(major, 0), NULL, "irq_dev"); 
	
	printk("major = %d \n",major);
	
	return 0;
}
void fourth_irq_exit()
{	
	unregister_chrdev(major,"irq");
	device_unregister(fourth_irq_class_dev);
	class_destroy(fourth_irq_class);
}


module_init(fourth_irq_init);
module_exit(fourth_irq_exit);

MODULE_LICENSE("GPL");  
