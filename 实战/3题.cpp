#include<stdio.h>
int main()
{
	int t,year,m,sum,month=11,n=0,day;
	printf("输入：");
	scanf("%d",&year);
	if(year%4==0&&year%100!=0||year%400==0)
    sum=31+29+31+30+31+30+31+31+30+31;
    else
	sum=31+28+31+30+31+30+31+31+30+31;
	t=(year-2015)/4*5+(year-2015)%4+4;
	if(t<-30||t>30) 
	{
	month+=t/30;
	if(month<0) month=-month;
	if(month==0) month=12;
	if(month>12)
	month=month%12;
	t=t%30;
}
	if(t<0) t=7+t%7;
	m=(t%7+sum)%7;
	if(m==0) m=7;
	if(m>5)
	n=3*7+13-m;
	else if(m==5)
	n=7*3+1;
	else
	n=3*7+6-m;
	printf("输出：%d年%d月%d日",year,month,n);
 } 
