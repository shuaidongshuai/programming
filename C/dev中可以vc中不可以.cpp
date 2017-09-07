#include<stdio.h>
int main()
{
	int i,n=10,a[n]; 		//vc中就不可以这样，，a的内存大小未知，尽管前面n=10 
	for(i=0;i<n;i++)
	{
		a[i]=i;
	printf("%d",a[i]);
	}
}
