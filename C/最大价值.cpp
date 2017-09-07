#include<stdio.h>
int main()
{
	int n,a[10001][2],sum,i;
	float average[10001],m=0,t;
	scanf("%d%d",&n,&sum);
	for(i=0;i<n;i++)
	{
		scanf("%d%d",&a[i][0],&a[i][1]);	
		average[i]=(float)a[i][1]/a[i][0];	
	}
	for(i=0;i<n;i++)
	{
		int j;
		for(j=i+1;j<n;j++)
		{
			if(average[i]<average[j])
			{
				t=average[i];
				average[i]=average[j];
				average[j]=t;
				t=a[i][0];
				a[i][0]=a[j][0];
				a[j][0]=t;
			 }
		}
	}
	for(i=0;i<n;i++)
	{
		if(sum>a[i][0])
		{
			m+=average[i]*a[i][0];
			sum-=a[i][0];
		}
		else
		{
			m+=average[i]*sum;
			break;
		}
	}
	printf("%.1f",m);
	return 0;
 } 
