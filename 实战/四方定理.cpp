#include<stdio.h>
#include<math.h>
int main()
{
	int sum;
	char n='a';
	printf("输入一个自然数：（只想看一个组合，输入完自然数后按‘空格’）\n");
	scanf("%d",&sum);
	scanf("%c",&n);
	int a,b,c,d;
	if(n==' ')
	{
	for(a=0;a<=sqrt(sum);a++)
	for(b=0;b<=sqrt(sum);b++)
	for(c=0;c<=sqrt(sum);c++)
	for(d=0;d<=sqrt(sum);d++)
		if(sum==a*a+b*b+c*c+d*d)
		{
		printf("%d=%d^2+%d^2+%d^2+%d^2\n",sum,d,c,b,a);
		goto loop;
	}
	loop:printf("\n只输出这一个");
}
	else
	{
			for(a=0;a<=sqrt(sum);a++)
	for(b=0;b<=sqrt(sum);b++)
	for(c=0;c<=sqrt(sum);c++)
	for(d=0;d<=sqrt(sum);d++)
		if(sum==a*a+b*b+c*c+d*d)
		printf("%d=%d^2+%d^2+%d^2+%d^2\n",sum,d,c,b,a);
	}
 } 
