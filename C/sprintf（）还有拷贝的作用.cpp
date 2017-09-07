#include<stdio.h>
int main()
{
	char a[5]="dong",b[5];
	sprintf(b,a);			//还有拷贝的作用   和 strcpy  效果一样 
	printf("%s",b);
 } 
