
#include <mach/regs-gpio.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include<linux/device.h>

struct class *fourthdrv_class;
struct class_device *fourthdrv_class_dev;

static unsigned long led_table [] = {
	S3C2410_GPB(5),
	S3C2410_GPB(6),
	S3C2410_GPB(7),
	S3C2410_GPB(8),
};

static unsigned int led_cfg_table [] = {
	S3C2410_GPIO_OUTPUT,
	S3C2410_GPIO_OUTPUT,
	S3C2410_GPIO_OUTPUT,
	S3C2410_GPIO_OUTPUT,
};

static int s3c24xx_leds_open(struct inode *inode, struct file *file)
{
	 int i;   
	for (i = 0; i < 4; i++) 
	{      
		// 设置GPIO引脚的功能：本驱动中LED所涉及的GPIO引脚设为输出功能     
		s3c2410_gpio_cfgpin(led_table[i], led_cfg_table[i]);  
	}   
	return 0;
}

static int s3c24xx_leds_ioctl(    struct inode *inode,     struct file *file,     unsigned int cmd,     unsigned long arg)
{   
	if (arg > 4) 
		return -EINVAL; 
   
	switch(cmd)
	{    
	case 0:        // 设置指定引脚的输出电平为0 
	s3c2410_gpio_setpin(led_table[arg], 0);  
	return 0; 
	case 1:        // 设置指定引脚的输出电平为1    
	s3c2410_gpio_setpin(led_table[arg], 1);     
	return 0;  
	default:     
	return -EINVAL;  
	}
}

static struct file_operations fourth_led_fops = {  
	.owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */ 
	.open   =   s3c24xx_leds_open,    
	.ioctl  =   s3c24xx_leds_ioctl,
};

int major;
	
int fourth_led_init()
{		

	major = register_chrdev(0 , "dong_leds",&fourth_led_fops );

	fourthdrv_class = class_create(THIS_MODULE,"leds_drv");
	fourthdrv_class_dev =  device_create(fourthdrv_class, NULL, MKDEV(major, 0), NULL, "myleds"); 
	
	printk("major = %d \n",major);
	
	return 0;
}
void fourth_led_exit()
{	
	unregister_chrdev(major,"dong_leds");
	class_destroy(fourthdrv_class);
}


module_init(fourth_led_init);
module_exit(fourth_led_exit);

MODULE_LICENSE("GPL");  