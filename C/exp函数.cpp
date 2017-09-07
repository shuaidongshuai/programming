#include<stdio.h>
#include<math.h>
int main()
{
	printf("e的1次方=%0.10f\n",exp(1));
	printf("e的2次方=%f",exp(2));
/*而在固定格式输出的时候，都默认的是6位
用double的时候f前面加l是没有效果的
你要输出长度，可以写，%0.8f，这样就是输出8个有效数字了*/
 } 
