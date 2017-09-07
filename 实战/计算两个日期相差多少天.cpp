#include<stdio.h>
#include<stdlib.h>
int mon[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int gep(int year)
{
	return (year%4==0&&year%100!=0||year%400==0);
}
int star(int month,int day)				//算前面时  包括了今天 
{
	int a=0;
	for(month=month-1;month>0;month--)
	{
		a+=mon[month];
	}
	return day+a;
}
int end(int month,int day)				//算后面时 没有包括今天 
{
	int a=0;
	for(month;month<13;month++)
	{
		a+=mon[month];
	}
	return a-day;
}
int disparity(int year1,int month1,int day1,int year2,int month2,int day2)
{
	int a=0;
	if(year1==year2)
	{
		return star(month2,day2)-star(month1,day1);
	}
	else
	{
		for(year1=year1+1;year1<year2;year1++)
		{
			a=a+365+gep(year1);
		}
	}
	return a+star(month2,day2)+end(month1,day1)+1;
}
int main()
{
	int a,c,b;
	printf("请输入第一个日期：如1996 2 22（按回车结束）\n");
	scanf("%d%d%d",&a,&b,&c);
	printf("请输入第二个日期：如2015 12 26\n");
	int  d,e,f;
	scanf("%d%d%d",&d,&e,&f);
	int result=disparity(a,b,c,d,e,f);
	printf("两个日期相差：%d天\n",result);
	system("pause");
 } 
 
 
 
 
 
 
 
 
