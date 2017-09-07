#include<stdio.h>
#include<stdlib.h>
int  add(int a,int b)
{
	int wei=0,jinwei=0;
	while(b!=0)
	{
		wei=a^b;		//wei 进行加法运算  但 在二进制中  都没有进位 
		jinwei=(a&b)<<1;//jinwei <<1 实现进位 
		a=wei;
		b=jinwei;
	}				//每迭代一次 jinwei都加了一个0 再与 wei又进行上一次运算  jinwei以按位与运算为0 的概率越来越大 
	return wei;
}
int aadd(int a,int b)	//为了证明 每次 迭代的两个值  相加  与原式相等 
{
	int wei,jinwei;
	wei=a^b;
	jinwei=(a&b)<<1
	;
	return wei+jinwei;
 }
 int aaadd(int a,int b)//too1 
 {
 	return a+b;
 }
int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	printf("%d+%d=%d\n",a,b,add(a,b));
	printf("%d+%d=%d\n",a,b,aadd(a,b));	
	printf("%d+%d=%d\n",a,b,aaadd(a,b));
}





 
