#include<stdio.h>
void dong(int *p,int m,int n)
{
	int i,j,t;
	for(i=0;i<m;i++)
	{
		t=*(p+n-1);
		for(j=n-1;j>0;j--)
		{
			*(p+j)=*(p+j-1);
		}
		*p=t;
	}
}
int main()
{
	int n,m,a[20],i;
	printf("你要输入几个数：");
	scanf("%d",&n);
	printf("请输入：");
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);	/*注意输入一个数字打空格*/ 
	printf("向后移动：");
	scanf("%d",&m);
	dong(a,m,n);
	for(i=0;i<n;i++)
	printf("%d  ",a[i]); 
}
