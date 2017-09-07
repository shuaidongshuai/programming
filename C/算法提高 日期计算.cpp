/*问题描述
 *已知2011年11月11日是星期五，问YYYY年MM月DD日是星期几？注意考虑闰年的情况。尤其是逢百年不闰，逢400年闰的情况。
 */
 //通过电脑咨询到2016年1月1日也是 星期五 
#include<stdio.h>
int judge(int year)
{
	if(year%4==0 && year%100!=0 || year%400==0)
	return 1;
	return 0;
}
int get_year(int year)
{
	int sum = 0;
	if(year>=2016)
	{
		while(year!=2016)
		{
			year--;//算的是前一年的日子  比如 2017 年，那么不能算 2017 年的天数  应该算2016 年的天数 
			if(judge(year))
			sum += 366;
			else
			sum += 365;			
		}	
	}
	else
	{
		while(year!=2016)
		{
			if(judge(year))
			sum += 366;
			else
			sum += 365;
			year++;
		}		
	}
	return sum;
}
int main()
{
	while(1)
	{
		int year,mon,day,sum=0;
		int month[13]={0,31,29,31,30,31,30,31,31,30,31,30,31};
		scanf("%d%d%d",&year,&mon,&day);
		if(year >= 2016)
		{
			sum = get_year(year);
			if(!judge(year))
			month[2] = 28;
			
			while(mon!=1)
			sum += month[--mon];//这里也要注意一下，是算前一个月的天数 
	
			sum += day-1+5;
			sum%=7;
			if(sum==0)
			sum = 7;
			printf("%d\n",sum);
		}
		else
		{
			sum = get_year(year);
			if(!judge(year))
			month[2] = 28;
			while(mon!=1)
			sum -= month[--mon];
			
			sum -= day ;
			sum %= 7;
			
						   //*************重点************// 
			sum = 5-1-sum;//这里必须用 星期 5 来减   因为是从 以前 到现在 这条时间线
						  //为什么多减1呢，答：2015/1/1 到 2015/12/31 有 365 天、、、、、2015/12/31 到 2016/1/1 有 1 天 
			if(sum <= 0)
			sum+=7;
			printf("%d\n",sum);
		 } 
	}
	 return 0;
}
/*最开始没有构造，get_year()这个函数，导致有些答案对  有些答案错 
**原因就在于，我是直接用year-- or year++ 这样每次 if(!judge(year)) 都不会执行 都是闰年
**用了这个函数  就可以少 一个  替换 year的变量了 
*/
