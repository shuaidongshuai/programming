#include<stdio.h>
int main()
{
	int i,j,t,a[3];
	scanf("%d%d%d",&a[0],&a[1],&a[2]);
	for(j=0;j<3;j++)
	{
		for(i=j+1;i<3;i++)
		{
			if(a[j]<a[i])
			{
				t=a[j];
				a[j]=a[i];
				a[i]=t;	
			}
		}
		printf("%d ",a[j]);
	}	
	return 0;
}
