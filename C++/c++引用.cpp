//c++中的引用
#include<stdio.h>
int main()
{
	int a = 4;
	int &b = a;//给 a 取别名  为  b   注意 ：引用类型 应该和 a 的类型一样 
	printf("%d  %d\n",a,b);
	
	b = 5;
	printf("%d  %d\n",a,b);
	
	printf("0x%x  0x%x\n",&a,&b);
		 
 } 
