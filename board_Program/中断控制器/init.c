//  中断控制器  有很多要用的寄存器   下面是我一天所弄懂的一些寄存器

#include "s3c2440.h"

/*
 * LED1-LED4  对应 GPB5_8
 */
#define GPB5_out        (1<<(5*2))      // LED1
#define GPB6_out        (1<<(6*2))      // LED2
#define GPB7_out        (1<<(7*2))      // LED3
#define GPB8_out        (1<<(8*2))      // LED4

/*
 * K1-K4 对应 GPG0 3 5 6
 */
#define GPG0_eint       (2<<(0*2))     // K1,  	的外部中断对应   EINT8		对应GPG0 3 5 6
#define GPG3_eint       (2<<(3*2))      // K2,  的外部中断对应   EINT11
#define GPG5_eint       (2<<(5*2))      // K3,					 EINT13
#define GPG6_eint       (2<<(6*2))      // K4,					 EINT14

void disable_watch_dog(void)
{
    WTCON = 0;  // 往这个寄存器里面写入 0  就可以关闭  看门狗
}

void init_led(void)
{
    GPBCON = GPB5_out | GPB6_out | GPB7_out | GPB8_out ;		// 设置为输出引脚
	//GPBDAT |= (~0);		// GPIO引脚用在外部中断 默认低电平触发   LED 会亮    初始化的时候并不想让他亮 
	// 上面这句话是网上复制的   经过试验可知是错误的  他不只是开始关闭了 LED  当中断发生 点亮LED 后 清除中断后（重新执行这段代码）LED会熄灭
	//这就导致了 点亮以后  一旦手松开  LED立马熄灭   不能实现 按一个键就一直点亮一个灯
}
void init_irq( )
{
    GPGCON  = GPG0_eint | GPG3_eint | GPG5_eint | GPG6_eint;//设置为中断  10  为中断
    
    EINTMASK &= (~(1<<8)) & (~(1<<11)) & (~(1<<13)) & (~(1<<14));//用来屏蔽 EINT 外部中断信号的寄存器  我们不希望他屏蔽 EINT8 11 13 14	( 1为屏蔽 0为通过 )
        
		// K1 K2 K3 K4	的外部中断 EINT8 11 13 14  优先级相同  都是 REQ1
		////所以不用像韦东山程序里那样再设置优先级了
		
		
		//让 EINT8 11 13 14 使能（感觉就是能用  能通过的意思）
    INTMSK  = ~(1<<5);
	//  这个也是一个 屏蔽外部中断的寄存器 和 EINTMASK不同的是  EINTMASK专用于屏蔽 EINT4--23 外部中断   EINT 对于INITMSK来说就是一个类
	// INTMSK 是用来屏蔽多个类的寄存器
	// INTMSK可以屏蔽0--31个类
	// EINT8_23刚好就是 第 5 个类  （有第0 个类）    
	// 0为通过  1 为屏蔽
}