#include<stdio.h>
int main()
{
	int x,sum;
	for(x=0;x<6;x++)
	for(sum=378;sum<=10605;sum++)
	if(sum==10605/(28-5*x)&&10605%(28-5*x)==0)
	{ 
	printf("total:%d\n",sum); 
	printf("A:%d\nB:%d\nC:%d",sum/5,sum-303-sum/5,303);
}
} 
