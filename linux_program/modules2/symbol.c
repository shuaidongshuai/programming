#include<linux/init.h>
#include<linux/module.h>
MODULE_LICENSE("GPL");

int add(int a,int b)
{
	return a+b;
}
int sub(int a,int b)
{
	return a-b;
}

static int a_init(void)
{
	return 0;
}
static void b_exit(void)
{
	
}

module_init(a_init);
module_exit(b_exit);

EXPORT_SYMBOL(add);
EXPORT_SYMBOL(sub);