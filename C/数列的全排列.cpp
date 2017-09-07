#include<stdio.h>
int n=0;
void swap(int *a,int *b)
{
	int t;
	t=*a;
	*a=*b;
	*b=t;
}
void change(int a[],int b,int c)
{
	if(b>=c)
	{
		for(int i=0;i<=c;i++)
		printf("%d  ",a[i]);
		n++;
		/*if(n%10==0)
		printf("\n");
		else*/
		printf("\n");
	}
	else
	{
		for(int j=b;j<=c;j++)
		{
			swap(&a[b],&a[j]);
			change(a,b+1,c);
			swap(&a[b],&a[j]);
		}
	}
}
int main()
{
	int a[]={0,1,2,3,4};
	change(a,0,4);
	printf("\ntotal=%d",n);
	return 1;
 } 
