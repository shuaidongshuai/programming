//已知2011年11月11日是星期五，问YYYY年MM月DD日是星期几？
//（假如条件允许），电脑下面的时间可以给你提供很全面正确的信息，有了基础天数后，以本题为例，2011年1月1日是星期6 
#include<iostream>
#include<cmath>
using namespace std;

bool leap(int year)
{
	if(year%4==0&&year%100!=0)
	return true;
	if(year%400==0)
	return true;
	return false;
} 

int getYD(int year)
{
	int sum=0;
	int i;
	if(year<=2011)
	{
		for(i=year;i<2011;i++)
		{
			if(leap(i))
			sum+=366;
			else
			sum+=365;	
		}
	}
	if(year>2011)
	{
		for(i=2011;i<year;i++)
		{
			if(leap(i))
			sum+=366;
			else
			sum+=365;
		}
	}
	return sum;
}

int getMD(int year,int mon,int day)
{
	int i;
	int sum=0;
	for(i=1;i<mon;i++)
	{
		if(i==1||i==3||i==5||i==7||i==8||i==10||i==12)
		sum+=31;
		if(i==4||i==6||i==9||i==11)
		sum+=30;
		if(i==2&&leap(year))
		sum+=29;
		if(i==2&&!leap(year))
		sum+=28;
	}
	sum=sum+day-1;
	return sum;
}



int main()
{
	int year,mon,day,sum;
	while(cin>>year>>mon>>day)
	{
		sum=getYD(year);
		//cout<<getMD(year,mon,day)<<endl;;
		if(year<2011)
		{
			sum=sum-getMD(year,mon,day);
			//cout<<sum<<endl;
			cout<<(sum%7==6?7:abs(6-(sum%7)))<<endl;
		}
		else
		{
			sum=sum+getMD(year,mon,day);
			//cout<<sum<<endl;
			cout<<((6+(sum%7))>7?((6+(sum%7))%7):(6+(sum%7)))<<endl;
		}
		
		
	}
	return 0;
}
