#include<linux/init.h>
#include<linux/module.h>
#include"add_sub.h"
//#include<add_sub.h>
//#include "../add_sub/include/add_sub.h"
// 定义模块传递参数 a,b
static long a = 1;
static long b = 2;
static long symbol = 1;

static int test_init(void)
{
	long result = 0;
	printk(KERN_ALERT "test init \n");
	if(1==symbol)
		result = add_integer(a,b);
	if(1==symbol)
		result = sub_integer(a,b);
	printk(KERN_ALERT "The %s result is %ld",symbol=='+'?"Add":"Sub",result);
	return 0;
}
static void test_exit(void )
{
	printk(KERN_ALERT "test exit \n");
}
module_init(test_init);
module_exit(test_exit);
module_param(a, long ,S_IRUGO);
module_param(b, long ,S_IRUGO);
module_param(symbol, long ,S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("chen ming dong");//author
