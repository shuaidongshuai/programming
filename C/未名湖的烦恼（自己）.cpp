#include<stdio.h>
int m=0;
void swap(char *a,char *b)
{
	char t;
	t=*a;
	*a=*b;
	*b=t;
}
void sort(char a[],int b,int n)
{
	int i;
	if(b>=n)
	{
		int x=0,sum=1;
		for(i=0;i<=n;i++)
		{
			if(a[i]-'0'>0)
			sum+=1;
			else
			sum-=1;
			
			if(sum<0)
			x--;
			printf("%c",a[i]);
		}
		printf("\n");
			if(0==x)
			m++;
	}
	else
	{
		for(i=b;i<=n;i++)
		{
			swap(&a[b],&a[i]);
			sort(a,b+1,n);
			swap(&a[b],&a[i]);				

		}
	}
}
int main()
{
	char str[20];
	int i,a,b,c,d;
	scanf("%d%d",&a,&b);
	for(i=0;i<a-1;i++)
	str[i]='1';
	for(i;i<a+b-1;i++)
	str[i]='0';
	sort(str,0,a+b-2);
	c=d=1;
	a-=1;
	while(a>1)
	{
		c*=a;
		a--;
	}
	while(b>1)
	{
		d*=b;
		b--;
	}
	printf("%d",m/c/d);
	return 0;
}
