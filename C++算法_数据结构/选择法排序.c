#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void paixu(int a[],int n)
{
	int i,j,t;
	for(i=0;i<n;i++)
	{
		for(j=i;j<n;j++)
		{
			if(a[i]>a[j+1])
			{
				t=a[i];
				a[i]=a[j+1];
				a[j+1]=t;
			}
		}
	}
	for(j=0;j<10;j++)
	{
	printf("%d\t",a[j]);
}
}
int main()
{
	srand(time(NULL));
	int a[10],i;
	printf("ÅÅÐòÇ°£º\n");
	for(i=0;i<10;i++)
	{
		a[i]=rand()*100/32767;
		printf("%d\t");
	}
	printf("\nÅÅÐòºó£º\n");
	paixu(a,10);
}
