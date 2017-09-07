#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
//头文件可以直接拷贝出来不够再添
int major;

int first_drv_open (struct inode *node, struct file *file)
{
	printk("hello dong \n this is you first open\n");
	return 0;
}
ssize_t first_drv_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	printk("hello dong \n this is you first write\n");
	return 0;
}

static struct file_operations first_drv_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   first_drv_open,     
	.write	=	first_drv_write,	   
};

int first_drv_init()
{
	//register_chrdev返回的是主设备号		0  表示自动申请一个主设备号
	major = register_chrdev(0,"dong",&first_drv_fops);//注册，，（把first_drv_fops结构（结构中有我们实现的函数）告诉内核）
	printk("major = %d\n",major);
	return 0;
}

void first_drv_eixt()
{
	unregister_chrdev(major,"dong");//需要主设备号和设备名来注销
} 

module_init(first_drv_init);
module_eixt(first_drv_eixt);
