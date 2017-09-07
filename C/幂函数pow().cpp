#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
	int x=2,y=4;
	printf("%d^%d=%d\n",x,y,(int)pow(x,y));
	if(pow(x,y)>x)		//单精度浮点也可以与 整形比较大小 
	printf("dong"); 
 } 
