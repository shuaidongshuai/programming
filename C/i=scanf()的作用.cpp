#include<stdio.h>
int main()
{
	int a,b,i,c;
	i=scanf("%d%d%c",&a,&b,&c);						/*输入4587 1246dgdn45试试*/ 
	printf("%d\t%d\t%c",a,b,c);
	printf("\n%-5d",i); 							/*输出的是a,b,c被成功输入的个数*/ 
 } 
/*
4587 1246dgdn45
4587 1246 d
3
-------------------------------
123
123
123     123

3
*/ 
