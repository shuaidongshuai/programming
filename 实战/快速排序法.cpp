#include<stdio.h>
#include<time.h>
#include<stdlib.h>
void quick(int a[],int left,int right)
{
	int l,r,t;
	r=right;
	l=left;
	t=a[l];
	if(l<r)
	{
	while(l<r)
	{
		while((l<r)&&(a[r]>=t))
		r--;
		a[l]=a[r];
		while((l<r)&&(a[l]<=t))
		l++;
		a[r]=a[l];
	}
	a[l]=t;
	quick(a,left,l-1);
	quick(a,r+1,right);
}
}
int main()
{
	srand(time(NULL));
	int i,N=200,a[N];
	for(i=0;i<N;i++)
	{
		a[i]=rand()%100;
	}
	for(i=0;i<N;i++)
	printf("%d\t",a[i]);
	printf("\ndong\n");
	quick(a,0,N-1);
	for(i=0;i<N;i++)
		printf("%d\t",a[i]);
}
