#include<stdio.h>
struct dong{
	int l,r,
	sum,//用来记录 左右子树的和 
	m;//用来记录 左右子树中最大的一个 
}a[1000000];
int max(int a,int b)
{
	return a>b?a:b;
 } 
int init(int l,int r,int i)
{ 
	a[i].l  = l;
	a[i].r 	= r;
    a[i].m = 0;
    a[i].sum = 0;	
	if(l!=r)
	{
		int mid = (l+r)/2;
		init(l,mid,2*i);
		init(mid+1,r,2*i+1);
	}
}
void insert(int l,int n,int i)
{
	if(a[i].l == l && a[i].r == l)
	{
		a[i].m = a[i].sum = n;
		return ;
	}
        
	int mid = (a[i].r +a[i].l)/2;
	if(l>mid)
		insert(l,n,2*i+1);//向右遍历
	else
		insert(l,n,2*i);//向左遍历	
	
	a[i].sum = a[i*2].sum + a[i*2+1].sum; 
	a[i].m   = max(a[i*2].m,a[i*2+1].m);
}
int find_sum(int l,int r,int i)
{
	if(a[i].l == l && a[i].r == r)
	return a[i].sum;
	
	int mid = (a[i].l + a[i].r)/2;
	if(l>mid)//不能填等于，等于的时候是向左遍历 
		return find_sum(l,r,2*i+1);//向右遍历
	else if(r<=mid)
		return find_sum(l,r,2*i);//向左遍历
	else
		return find_sum(l,mid,2*i) + find_sum(mid + 1, r,2*i+1);//在百度上得到提示（原来这样做就能  表示任意区间 ）、、当mid在l和r之间时 
	//当mid在l和r之间时 这个问题困扰我很久，我以为 当出现分叉就不能表示那个区间了。。。原来是我还不会 
 } 
int find_max(int l,int r,int i)
{
	if(a[i].l == l && a[i].r == r)
	return a[i].m;
	
	int mid = (a[i].l + a[i].r)/2;
	if(l>mid)
		return find_max(l,r,2*i+1);//向右遍历
	else if(r<=mid)
		return find_max(l,r,2*i);//向左遍历
	else
		return max(find_max(l,mid,2*i) , find_max(mid + 1,r,2*i+1));
}
int main()
{
	int n,m,i,j,x,y,z;
	scanf("%d%d",&n,&m);
	
	init(1,n,1);
    for(i = 1; i<=n; i++)
    {
        scanf("%d",&j);
        insert(i,j,1);
    }
    while(m--) 
	{
		scanf("%d%d%d",&x,&y,&z);

		if(x == 1)
			insert(y,z,1);		
		
		else if(x == 2)
			printf("%d\n",find_sum(y,z,1));
		else if(x == 3)
			printf("%d\n",find_max(y,z,1));
	}		
	return 0;
 } 
/*
有n个格子，从左到右放成一排，编号为1-n。

共有m次操作，有3种操作类型：

1.修改一个格子的权值，

2.求连续一段格子权值和，

3.求连续一段格子的最大值。

对于每个2、3操作输出你所求出的结果。

输入格式
第一行2个整数n，m。

接下来一行n个整数表示n个格子的初始权值。

接下来m行，每行3个整数p,x,y，p表示操作类型，p=1时表示修改格子x的权值为y，p=2时表示求区间[x,y]内格子权值和，p=3时表示求区间[x,y]内格子最大的权值。

输出格式
有若干行，行数等于p=2或3的操作总数。

每行1个整数，对应了每个p=2或3操作的结果。

样例输入
4 3
1 2 3 4
2 1 3
1 4 3
3 1 4
样例输出
6
3
数据规模与约定
对于20%的数据n <= 100，m <= 200。

对于50%的数据n <= 5000，m <= 5000。

对于100%的数据1 <= n <= 100000，m <= 100000，0 <= 格子权值 <= 10000。
*/
