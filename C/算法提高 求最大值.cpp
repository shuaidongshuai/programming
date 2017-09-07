#include<stdio.h>
int sum[101],q=0;
void dong(int a[][2],int n)
{
	int b,c,i,l=0,r=0;
	for(i=0;i<n;i++)
	{
		l+=a[i][0];
		r+=a[i][1];	
	}
	if(l>=0&&r>=0)
	{
		sum[q]=l+r;
		q++;
	}
	else
	{
		for(i=0;i<n;i++)
		{
			if((a[i][0]!=0)&&(a[i][1]!=0))
			{
			b=a[i][0];
			c=a[i][1];
			a[i][0]=a[i][1]=0;
			dong(a,n);
			a[i][0]=b;
			a[i][1]=c;
			}
		}
	}
}
int main()
{
	int i,t,j=0,n,a[101][2],b[101][2];
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d%d",&a[i][0],&a[i][1]);
	}
	for(i=0;i<n;i++)
	{
		t=a[i][0]+a[i][1];
		if(t>=0)
		{
			b[j][0]=a[i][0];
			b[j][1]=a[i][1];
			j++;		
		}
	}
	dong(b,j);
	for(i=1;i<j;i++)
	{
		if(sum[0]<sum[i])
		sum[0]=sum[i];
	}
	printf("%d",sum[0]);
	return 0;
 } 
