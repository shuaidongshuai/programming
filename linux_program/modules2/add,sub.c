#include<linux/init.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");
extern int add(int a,int b);
extern int sub(int a,int b);

static int __init a_init(void)
{
	int a=add(1,2);
	printk("1+2=%d\n",a);
	return 0;
}
static void __exit b_exit(void)
{
	
}
module_init(a_init);
module_exit(b_exit);