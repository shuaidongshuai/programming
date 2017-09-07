#include<stdio.h>
int main()
{
	int year,month,day,sum;
	printf("please input year,month,day\n");
	scanf("%d,%d,%d",&year,&month,&day);
	switch(month)
	{
		case 1:sum=0;break;
		case 2:sum=31;break;
		case 3:sum=31+28;break;
		case 4:sum=31+28+31;break;
		case 5:sum=31+28+31+30;break;
		case 6:sum=31+28+31+30+31;break;
		case 7:sum=31+28+31+30+31+30;break;
		case 8:sum=31+28+31+30+31+30+31;break;
		case 9:sum=31+28+31+30+31+30+31+30;break;
		case 10:sum=31+28+31+30+31+30+31+30+31;break;
        case 11:sum=31+28+31+30+31+30+31+30+31+30;break;
        case 12:sum=31+28+31+30+31+30+31+30+31+30+31;break;
        default: printf("data error");break;
	}
	sum=sum+day;
	if(year%400==0||(year%100==0&&year%4==0))
	{
		if(month>2)
		sum++;
	}
	printf("½á¹ûÊÇ£º%d",sum);
 } 
