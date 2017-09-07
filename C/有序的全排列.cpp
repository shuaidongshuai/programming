//要实现有序的全排列  必须输入有序  如1 2 3 那么就是从小到大排列   3 2 1 就是从大到小
// 如果真的有需要  可以对输入的数组进行排序   然后在 dfs 排序 
#include<stdio.h>
int a[100],aa[100],b[100],n;		// aa[] 就是把最初的a[]数组给记住 
void dfs(int t)
{
	if(t==n)
	{
		for(int i=0;i<n;i++)
		printf("%d",a[i]);
		printf("\n");
	}
	else
	{
		for(int j=0;j<n;j++)//每次递归  j 都必须从0  开始 到达第一个 b[j]为 0 的地方停止（aa[]还未被1覆盖的最小值）  这样才能有序 
		if(!b[j])
		{
			b[j]=1;
			a[t]=aa[j]; 
			dfs(t+1); 
			b[j]=0;
		}
	}
}
int main()
{
	scanf("%d",&n);
	int i,j;
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
		aa[i]=a[i];	
	}
	dfs(0);
	
	
	return 0;
 } 
