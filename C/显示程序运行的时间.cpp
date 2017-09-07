#include<stdio.h>
#include<time.h>
int main()
{
	int i,j,a[200][200];
	time_t star,end;
	star=time(NULL);		//计时开始 
	for(i=0;i<200;i++)
	for(j=0;j<100;j++)
	{
		a[i][j]=100*i+10*j;
	printf("%d\t",a[i][j]);
}
	end=time(NULL);			//程序计时结束 
	printf("\n\n%f\n",difftime(end,star));	//difftime算出时间差 
 } 
