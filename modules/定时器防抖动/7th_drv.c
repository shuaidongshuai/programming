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

struct class *seven_drv_class;
struct class_device *seven_drv_class_device;

static DECLARE_WAIT_QUEUE_HEAD(button_waitq);
static volatile int ev_press = 0;


struct timer_list buttons_timer;/*定义定时器*/

struct pin_desc{
	unsigned int pin;
	unsigned int key_val;
};
static unsigned char key_val;

struct pin_desc pins_desc[4] = {
	{S3C2410_GPG(0),0x1},
	{S3C2410_GPG(3),0x2},
	{S3C2410_GPG(5),0x3},
	{S3C2410_GPG(6),0x4},
};

struct pin_desc *irq_pd;

static irqreturn_t buttons_irq(int irq, void *dev_id)
{
	/*每来一个中断就暂停10ms*/
	/*10ms启动定时器*/
	irq_pd = (struct pin_desc*)dev_id;
	/*修改定时器的超时时间*/
	mod_timer(&buttons_timer, jiffies + HZ /100);//expire 满期
	return IRQ_HANDLED;
}

static int seven_irq_open(struct inode *inode, struct file *file)
{
	request_irq(IRQ_EINT8,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K1",&pins_desc[0] );
	request_irq(IRQ_EINT11,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K2",&pins_desc[1] );
	request_irq(IRQ_EINT13,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K3",&pins_desc[2] );
	request_irq(IRQ_EINT14,buttons_irq,IRQ_TYPE_EDGE_BOTH,"K4",&pins_desc[3] );
	
	return 0;
}

int seven_irq_close(struct inode *inode, struct file *file)
{
	free_irq(IRQ_EINT8, &pins_desc[0] );
	free_irq(IRQ_EINT11,&pins_desc[1] );
	free_irq(IRQ_EINT13,&pins_desc[2] );
	free_irq(IRQ_EINT14,&pins_desc[3] );
}

ssize_t seven_irq_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	if(size!=1)
	return -EINVAL;
	
	//没有中断 放入等待队列
	wait_event_interruptible(button_waitq,ev_press);
	
	/*如果有按键发生*/
	ev_press = 0;
	copy_to_user(buf,&key_val, size);
	
	return 0;
}

struct file_operations seven_drv_fops = {
	.owner 		=  	THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */ 
	.open 		=   	seven_irq_open,    
	.release		=	seven_irq_close,
	.read 		=  	seven_irq_read,
};

void buttons_timer_function(unsigned long data)
{
	struct pin_desc *pindesc = irq_pd;
	unsigned int pinval = 0;

	if(!pindesc)/*只有发生中断才不返回，如果pindesc == 0 说明没发生中断*/
	return 0;
	
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
	
}

int major;
int seven_drv_init()
{
	init_timer(&buttons_timer);/*初始化定时器*/
	buttons_timer.function = buttons_timer_function;/*设置他的处理函数buttons_timer_function*/
	add_timer(&buttons_timer);
	
	major = register_chrdev( 0, "KEY_irq", &seven_drv_fops);

	seven_drv_class = class_create(THIS_MODULE,"irq");
	seven_drv_class_device = device_create(seven_drv_class,NULL,MKDEV(major, 0),NULL,"irq");

	printk("major = %d\n",major);
	return 0;
}
void seven_drv_exit()
{
	unregister_chrdev(major,"irq");
	class_destroy(seven_drv_class);
	device_unregister(seven_drv_class_device);
}


module_init(seven_drv_init);
module_exit(seven_drv_exit);

MODULE_LICENSE("GPL");

