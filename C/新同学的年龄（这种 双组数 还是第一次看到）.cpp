#include<stdio.h>
#include<math.h>
int main()
{
	int i,age,a,b,c[10],d[10]={0};	//d[10]={0}代表数组全是0 
	for(age=11;age<100;age++)
	{
		a=pow(age,3);
		b=pow(age,4);
		if(a>=1000&&b>=100000)
		{
			for(i=0;i<4;i++)
			{
				c[i]=a%10;
				a=a/10;
			}
			for(;i<10;i++)
			{
				c[i]=b%10;
				b=b/10;
			}
			for(i=0;i<10;i++)
			d[c[i]]++;			//双数组，判断c[i]中是否有重复的数 
			for(i=0;i<10;i++)
			if(d[i]>1)
			break;
			if(i==10)
			printf("他是%d岁",age);
		}
	 } 
}
