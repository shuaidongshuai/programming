#include<stdio.h>
int main()
{
	int i,n,a[1001],b=0,t[2];
	scanf("%d",&n);
	for(i=0;i<n;i++)
	scanf("%d",&a[i]);
	t[0]=t[1]=a[0];
	for(i=0;i<n;i++)
	{
		if(t[0]<a[i])
		t[0]=a[i];
		if(t[1]>a[i])
		t[1]=a[i];
		b+=a[i];
	}
	printf("%d\n",t[0]);
	printf("%d\n",t[1]);
	printf("%d\n",b);
	return 0;
 } 
