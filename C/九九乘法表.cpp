#include<stdio.h>
int main()
{
	int x=1,y=1;
	while(x<=9)
	{
	y=1;
	while (y<=x)
	{
		printf("%d*%d=%d\t",y,x,x*y);
		y++;
	}
	printf("\n"); 
	x++;
	 } 
	 printf("作者:陈明东\n");
 }  
