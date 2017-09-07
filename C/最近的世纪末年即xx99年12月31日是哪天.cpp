#include<stdio.h>
int main()
{
	int i=1999,day=5;
	while(1)
	{
		i=i+1;
		if(i%4==0&&i%100!=0||i%400==0)
			day=day%7+366;
		else
			day=day%7+365;
		if(day%7==0&&i%100==99)
		{
			printf("%d",i);
			break;
		}
	}
}
