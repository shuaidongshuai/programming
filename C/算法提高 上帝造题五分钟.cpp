#include<stdio.h>
int a[1985];
void select(int b,int c)
{
	int i,t=a[b];
	for(i=b;i<=c;i++)
	{
		if(t>a[i])
		t=a[i];
	}
	printf("%d\n",t);
}
int main()
{
	int n,q,i,b[1989][2];
	scanf("%d%d",&n,&q);
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);
	for(i=0;i<q;i++)
	{
	scanf("%d%d",&b[i][0],&b[i][1]);		
	select(b[i][0],b[i][1]);	
	}
	return 0;
 } 
