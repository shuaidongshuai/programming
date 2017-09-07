//还有问题   无法实现  任意区间和   只能实现部分区间 
#include<stdio.h>
struct{
	int r,l,sum;
}a[100];
int b[100]={1,2,1,2,1,2,0};
void init(int l,int r,int i)
{
	a[i].l = l;//记录左区间 
	a[i].r = r;//记录右区间 
	 
	if(r == l)
	a[i].sum = b[l];
	else
	{
		int mid = (l+r)/2;
		init(l,mid,2*i);
		init(mid+1,r,2*i+1);
		
		a[i].sum = a[i*2].sum + a[2*i+1].sum;
	}
}
int find_sum(int l,int r,int i)
{
	if(a[i].l == l && a[i].r == r)
	return a[i].sum;
	
	int mid = (a[i].l+a[i].r)/2;
	if(r<=mid)				//这一定不能少 
	return find_sum(l,r,2*i);
	else						// 当 右边界  小于 总边界 执行 上一步   否则执行这一步 
	return find_sum(l,r,2*i+1);		
}
int main()
{
	init(0,6,1);//从0 位置 到 5 位置 , 根节点 为 1 
	
	for(int i=1;i<13;i++)
	printf("%d  ",a[i].sum);
	
	int x = find_sum(0,3,1);
	printf("\n在（0-3）区间内的和: %d\n",x);
	
	x = find_sum(4,6,1);
	printf("\n在（4-6）区间内的和: %d\n",x);
	
	x = find_sum(0,1,1);
	printf("\n在（0-1）区间内的和：%d\n",x);
	
	x = find_sum(6,6,1);
	printf("\n在（6-6）区间内的和：%d\n",x);
	
}
