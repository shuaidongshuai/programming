#include<linux/init.h>
#include<linux/module.h>
//#include "add_sub.h"
long add_integer(int a,int b)
{
	return a+b;
}
long sub_integer(int a,int b)
{
	return a-b;
}
// 导出上面两个函数
EXPORT_SYMBOL(add_integer);
EXPORT_SYMBOL(sub_integer);

MODULE_LICENSE("Dual BSD/GPL");