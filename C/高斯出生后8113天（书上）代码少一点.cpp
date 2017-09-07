#include<stdio.h>
int main()
{
	int year=1777,month=4,day=30;
	int a[]={0,31,29,31,30,31,30,31,31,30,31,30,31},i;
	for(i=1;i<8113;i++)
	{
		if(month==2&&year%4==0&&year%100!=0||year%400==0)
			a[2]=29;
		else
			a[2]=28;
		day=day%a[month]+1;
		if(day==1)
		{
			month=month%12+1;
			if(month==1)
			year++;
	}
}
	printf("%d-%d-%d\n",year,month,day);
}
