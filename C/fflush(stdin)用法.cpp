#include<stdio.h>
int main()
{
	char a[20],c;
	scanf("%s",a);
	fflush(stdin);/*感觉和c=getchar()一样的效果*/ 
	c=getchar();
	printf("%s  %c",a,c);
 } 
