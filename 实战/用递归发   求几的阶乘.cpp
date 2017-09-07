#include<stdio.h>
int dong(int i)
{
	int sum;
	if(i==0) sum=1;
	else 
	sum=i*dong(i-1); 
	return sum;
}
int main()
{
	int sum,j;
	printf("输入一个数：");
	scanf("%d",&j);
	sum=dong(j);
	printf("%d的阶乘为：%d",j,sum);
}
