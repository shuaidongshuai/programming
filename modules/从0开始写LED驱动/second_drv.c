#include<linux/module.h>
#include<linux/init.h>
#include <linux/io.h>//ioremap函数要用到
#include<linux/cdev.h>//用到了cdev这个结构
#include<linux/fs.h>//用到了file_operations 这个结构
#include<linux/device.h>//device_create  和  class_creat头文件存放的地方
//头文件可以直接拷贝出来不够再添
//unsigned long *GPBCON = NULL;
//unsigned long *GPBDAT = NULL;
static unsigned long gpio_va;
#define GPBCON  (*(volatile unsigned long *)gpio_va)			//GPBCON  代表了指针指向的内容  如果换成上面注释的声明，就相当于  *GPBCON（也是地址的内容）
#define GPBDAT  (*(volatile unsigned long *)(gpio_va+4))
int second_drv_open (struct inode *node, struct file *file)
{
	printk("hello dong \n this is you second open\n");
	
	GPBCON = 1<<10 | 1<<12 | 1<<14 | 1<<16;
	GPBDAT = 0xf<<5;
	
	
	//GPBCON = 1<<10 | 1<<12 | 1<<14 | 1<<16;
	//GPBDAT |= 0xf<<( 4 + 1 );
	return 0;
}
ssize_t second_drv_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	printk("hello dong \n this is you second write\n");
	return 0;
}

static struct file_operations second_drv_fops = {
    .owner  =   THIS_MODULE,    /* 这是一个宏，推向编译模块时自动创建的__this_module变量 */
    .open   =   second_drv_open,     
	.write	=	second_drv_write,	   
};

int major;

static struct class *second_drv_class;//定义一个类
static struct class_device	*second_drv_class_dev;//定义一个类 的设备

int second_drv_init()
{
	gpio_va = ioremap(0x56000010, 0x100000);
	
	//register_chrdev返回的是主设备号		0  表示自动申请一个主设备号
	major = register_chrdev(0,"dong",&second_drv_fops);//注册，，（把second_drv_fops结构（结构中有我们实现的函数）告诉内核）
	
	second_drv_class = class_create(THIS_MODULE, "dongdev");//创建一个类	class_create(owner, name)

	//在类下建立一个设备，设备将位于/dev/dong_dev			MKDEV(主设备号，次设备号)  把主次合成  dev_t类型的（32位 unsigned int）
	second_drv_class_dev = device_create(second_drv_class, NULL, MKDEV(major, 0), NULL, "dong_dev"); 
	
	printk("major = %d\n",major);
	return 0;
}

void second_drv_eixt()
{
	unregister_chrdev(major,"dong");//需要主设备号和设备名来注销
	
	device_unregister(second_drv_class_dev);//删除/dev/dong_dev这个设备节点
	class_destroy(second_drv_class);//删除这个类
}

MODULE_LICENSE("GPL"); 

module_init(second_drv_init);
module_eixt(second_drv_eixt);
