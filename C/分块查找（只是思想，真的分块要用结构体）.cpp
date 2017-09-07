#include<stdio.h>
int main()
{
	int x,i,j,a[]={2,3,4,6,7,8,9,10,12,13,14,15,16,20,24};
	for(i=0;i<15;i++)
		printf("%d\t",a[i]);
	printf("\nqing shu ru yi ge shu: ");
	scanf("%d",&x);
	for(i=2;i<15;i+=3)		//i=1,i+=3是3个三个一组，一共5组 。。分组越少，，下面if里面的语句越多 
	{
		if(x<=a[i])
		{
		if(x==a[i])					//分块查找的思想，if里面的代码只执行一次，节约了时间 
		{
			printf("是第%d个元素",i+1);
			break;
		}
		else if(x==a[i-1])
			{
			printf("是第%d个元素",i);
			break;
		}
		else if(x==a[i-2])
			{
			printf("是第%d个元素",i-1);
			break;
		}
		else 
		{
			i=-1;
		break;
		} 
	}
	}
	if(i==-1) printf("没有这个元素");
}
