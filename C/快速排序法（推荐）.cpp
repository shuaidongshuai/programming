#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int a[80];
void quick(int left,int right)
{
	int l=left,r=right;
	if(l<=r)
	{
		int t=a[l];
		while(l<r)
		{
			while(l<r&&a[r]>=t)//这两个 <= >=  可以换成一个等于<= >   或者 >= < 
				r--;
			a[l]=a[r]; 
			while(l<r&&a[l]<=t)
				l++;
			a[r]=a[l];
		}
		a[l]=t;
		quick(left,l-1);
		quick(r+1,right);
	}
} 
int main()
{
	int i;
	srand(time(NULL));
	for(i=0;i<80;i++)
	{
		a[i]=rand()%100;
		printf("%d\t",a[i]);
	}
	quick(0,79);
	printf("\n排序后：\n");
	for(i=0;i<80;i++)
		printf("%d\t",a[i]);
}
