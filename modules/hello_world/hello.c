#include<linux/module.h>
#include<linux/init.h>
//加载函数：当使用insmod命令加载模块时，会调用该函数
MODULE_LICENSE("GPL"); 
static int __init hello_init(void )
{
	printk("Hello , World \nchen ming dong");
	return 0;
}
//模块释放函数，当使用rmmod命令卸载模块时，会调用该函数
static void __exit hello_exit(void )
{
	printk("Goodbye , World\n");
}
module_init(hello_init);//内核模块的一个宏，用来声明模块的加载函数，
module_exit(hello_exit);//内核模块的一个宏，用来声明模块的卸载函数，
