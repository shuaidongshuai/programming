#include "s3c2440.h"
//这个是终端服务函数   可知只有发生中断（这里只是按键被按下）才会执行
void EINT_Handle()
{
	// INTOFFSET 一共有 31位（有0 位）
unsigned long oft = INTOFFSET; //INTOFFSET也是一个寄存器用来表示INTPEND寄存器哪位被置1了（第五位被置1  就等于5）经过INTMSK再进过优先级的选取都通过后 INTPEND 相应位被置 1
	// 和韦东山程序不一样  Mini2440 按键始终是 INTOFFSET =5  (如果按键被按下的话) 
    unsigned long val;

	val = EINTPEND;	// EINTPEND 可以准确的定位到 ENIT4--23中哪一个中断发生的  而 SRCPND 这个寄存器只能 定位到哪个类发生了  中断  (哪个位发生中断就被置1)
	
	 GPBDAT|=(0x0f<<5);          //所有LED熄灭,如果没有这一句，那么会出现一个结果，就是将程序下到板子里运行时，点亮了的灯不会熄灭
	
		if(val & (1<<8))
		GPBDAT &= ~(1<<5);
	
		if(val & (1<<11))
		GPBDAT &= ~(1<<6);
	
		if(val & (1<<13))
		GPBDAT &= ~(1<<7);
	
		if(val & (1<<14))
		GPBDAT &= ~(1<<8);

                
    //清清除中断
	if(oft==5)
    EINTPEND = (1<<8) | (1<<11) | (1<<13) | (1<<14); 
    SRCPND = 1<<oft;		//  oft   始终等于 5 		清除SRCPND寄存器，往某位写入1即可清楚此位
    INTPND = 1<<oft;		//清除顺序很重要：先是EINTPEND，然后是SRCPND，最后是INTPND
}