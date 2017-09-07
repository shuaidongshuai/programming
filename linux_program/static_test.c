#include<stdio.h>

void main1()
{
	static int a=0;
	printf("a=%d\n",a);
	a++;
}
int main()
{
	main1();
	main1();
	main1();
	int a=100;
	main1();
	main1();
	main1();
	
	printf("\n%d\n",a);
}