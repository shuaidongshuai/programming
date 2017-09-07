#include<stdio.h>
void sort(int a[],int n)
{
	int t,i,j;
	for(j=0;j<n-1;j++)
	for(i=j+1;i<n;i++)
	{
		if(a[j]>a[i])
		{
			t=a[j];
			a[j]=a[i];
			a[i]=t;
		}
	}
}
int main()
{
	int n,a[201],i,j;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}
	sort(a,n);
	for(j=0;j<n;j++)
	printf("%d ",a[j]);
	return 0;
}
