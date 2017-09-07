#include<stdio.h>
int main()
{
	int i,a,b,sum;
	for(a=1;a<100;a++)
	{
		b=a;
		sum=0;
	for(i=0;i<8;i++)
	{
		sum+=b;
		b=2*b; 
	}
	if(sum==765)
	{
	printf("%d  %d",a,b/2);
	break;
 } 
}
}
