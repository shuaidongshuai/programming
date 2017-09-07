#include<stdio.h>
#include<time.h>
#include<stdlib.h>
void quick(int a[],int left,int right)		//可以只有一个自定义函数 
{
	int r,l,t;
	l=left,r=right;
	t=a[l];
	if(l<r)
	{  
		while(l!=r)	//l<r 和 l!=r 效果一样，，这个排序法当跳出循环的时候  一定是 l = r 的时候，，而有的快速排序法是  l = r 或者 l = r+1 也就是 l>r才能跳出循环 
		{
			while(l<r&&a[r]>=t)		//又出错 了,,记住一定有等于，不然会出现左右两个值一直互换，死循环 
			r--;
			a[l]=a[r];
			while(l<r&&a[l]<=t)
				l++;
			a[r]=a[l];
		}
		a[l]=t;
		//这种排序法感觉还是挺好，不容易出错，，因为跳出循环  一定是 l = r的时候 下面 两个 l-1 都可以换成 r-1   
		quick(a,left,l-1);
		quick(a,l+1,right);		//right不能改为49,因为第一次递归可能没事，第二次递归right就不再是79  可能是l-1 
	}
}
int main()
{
	int i,a[80];
	srand(time(NULL));
	for(i=0;i<80;i++)
	{
		a[i]=rand()%100;
		printf("%d\t",a[i]);
	}
	quick(a,0,79);
	printf("\n排序后：\n");
	for(i=0;i<80;i++)
		printf("%d\t",a[i]);
}
