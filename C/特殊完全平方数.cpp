#include<stdio.h>
int main()
{
	int i,j,ge,shi,bai;
	for(i=100;i<999;i++)
	for(j=10;j<i;j++)
	{
		ge=i%10;
		shi=i/10%10;
		bai=i/100;
		if(j*j==i&&(ge==shi||ge==bai||shi==bai))
		printf("%d\n",i);
	}
 } 
