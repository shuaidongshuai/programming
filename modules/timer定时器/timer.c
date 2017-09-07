#include<linux/module.h>
#include<linux/init.h>
#include<linux/timer.h>
//#include<linux/kernel.h>
//#include<asm/uaccess.h>
MODULE_LICENSE("GPL");

void timer_function(int para)//时间到了就执行这个函数
{
	printk("Timer Expired and para is %d !!\n",para);
}

struct timer_list timer;

int timer_init()
{
	init_timer(&timer);
	
	timer.data = 100;//结构中的.data 的值将赋给 函数中int para （这就相当于给上面函数 para 这个变量赋值为 100 ）
	
	timer.expires = jiffies + (5 * HZ);	// HZ 默认为1000 如果HZ=1000 那jiffies就是每秒减去1000    这句话就相当于 5 s 后定时器结束
	
	timer.function = timer_function;//定时器结构中可以调用一个函数，这个函数有我们定义（定时器倒计时完了就执行这个函数）
	
	add_timer(&timer);	//启动定时器（上面是初始化）
	return 0;
}

void timer_exit()
{
	del_timer(&timer);	//关闭定时器（在定时器没有结束时，执行这个函数将会取消定时器）
}
module_init(timer_init);
module_exit(timer_exit);