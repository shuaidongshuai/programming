#include<stdio.h>
int main()
{
    char ch;
	int sum;
	sum=0;
	printf("«Î ‰»Î£∫");
	while(ch!='\n')
	{
		ch=getchar();
		if(ch<'0'||ch>'9')
		{
			continue;
		}
		sum++;
	 }
	 printf("sum=%d",sum);
}
