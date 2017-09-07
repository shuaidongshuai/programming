#include<linux/init.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
static char *name="chen ming dong";
static int age =20;

module_param(age,int ,S_IRUGO);
module_param(name,charp,S_IRUGO);

static int hello_init(void)
{
	printk(KERN_EMERG"name:%s\n",name);
	printk(KERN_EMERG"age:%d\n",age);
	return 0;
}
static void hello_exit(void)
{
	printk(KERN_INFO"goodbye\n");
}
module_init(hello_init);
module_exit(hello_exit);
