#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
int D(void)
{
	int *p=NULL;
	int a = 6;
	printk("d\n");	
	*p = a+12;
}
int C(void)
{
	printk("c\n");
	D();
}
int B(void)
{
	printk("b\n");
	C();
}
int A(void)
{
	printk("A\n");
	B();
}
int opps_init(void)
{
	int djfk=10;
	printk("oppo\n");
	A();
	return 0;
}
void opps_exit(void)
{
	
}

module_init(opps_init);
module_exit(opps_exit);
