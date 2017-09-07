#include<stdio.h>
int main()
{
	int b[4],*p,a[4]={1,2,3,4},i;
	p=b;					//相当于给p一个确定的内存，让p指向b的地址，，然后对地址进行-----，没有这一步无法执行下一步 
	for(i=0;i<4;i++)
	{
	*p=a[i];				//相当于b[0]=a[i] 
	p++;
	}
	for(i=0;i<4;i++)
	{
	printf("%d",b[i]);
}
}
