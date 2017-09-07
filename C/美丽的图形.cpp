#include<stdio.h>
int main()
{
	int i,j,n,m;
	scanf("%d%d",&n,&m);
	char a[27];
	for(i=0;i<m;i++)
	a[i]='A'+i;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%c",a[j]);
		}
		for(j=m-2;j>=0;j--)
		{
			a[j+1]=a[j];
		}
		a[0]='A'+i+1;
		printf("\n");
	}
	return 0;
}
