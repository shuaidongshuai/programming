//还有问题   无法实现  任意区间和   只能实现部分区间 
#include<stdio.h>
int a[100],b[100]={0,1,2,3,4,5,4,0};
int init(int l,int r,int i)
{ 
	if(r == l)
	a[i] = b[l];
	else
	{
		int mid = (l+r)/2;
		init(l,mid,2*i);
		init(mid+1,r,2*i+1);
		
//		a[i] = a[i*2] + a[2*i+1];
		a[i] = a[2*i] > a[2*i+1] ? a[2*i] : a[2*i+1];
	}
}
int main()
{
	init(5,6,1);//其实只需要这一个 函数就够了（只是说每次找区间和 的时候都要从新构建一次 线段树），第一二个参数就是要查到的区间 （区间从0开始的） 
	
	for(int i=1;i<13;i++)
	printf("%d  ",a[i]);
	printf("\n%d\n",a[1]);
}
