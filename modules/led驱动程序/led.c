#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/io.h>//ioremap函数要用到
#include "led.h"

MODULE_LICENSE("GPL"); 

//为什么不用 #define LEDCON (*(volatile unsigned *)0x56000010)	这样的表示方法？	答：不能直接操作物理地址
#define LEDCON 0x56000010
#define LEDDAT 0x56000014
unsigned int *led_config;
unsigned int *led_data;

struct cdev led_dev;
dev_t devno;

int led_open(struct inode *node, struct file *filp)
{
	//记住 Linux 系统中不能直接操作物理地址，ioremap可以吧物理地址转化成虚拟地址
	led_config = ioremap(LEDCON,4);//1物理地址，2大小（4字节  换成二进制就是 32位）
	//往寄存器里面写入数据，，也不能直接赋值  需要用到writel
	writel(1<<10 | 1<<12 | 1<<14 | 1<<16,led_config);//把第一个参数 led_config寄存器中
	
	led_data = ioremap(LEDDAT,4);
	return 0;
}
long led_ioctl(struct file *filp, unsigned int cmd , unsigned long arg)
{
	switch(cmd)//注意这里的 cmd  是  int 型 的
	{
		case LED_ON:writel(0x0,led_data); return 0;
		case LED_OFF:writel(0xf<<5,led_data); return 0;
		default: return -EINVAL;
	}
	return 0;
}

static struct file_operations led_fops =
{
	.open = led_open,
	.unlocked_ioctl = led_ioctl,
};

static int led_init()
{
	cdev_init(&led_dev, &led_fops);
	
	alloc_chrdev_region(&devno,0,1,"dev_dong");
	cdev_add(&led_dev,devno , 1);
	
	return 0;
}
static void led_exit()
{
	cdev_del(&led_dev);
	unregister_chrdev_region(devno,1);
}

module_init(led_init);
module_exit(led_init);
