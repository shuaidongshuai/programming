//对0--9 进行从小打大的全排列 
#include<stdio.h>
#define LONG 5		//长度
#define M 5			//0 - 5     0 - 9 太长了 
int a[10], b[10], sum = 0;
void sort(int n)
{
	if (n == M)
	{
		for (int i = 0; i<n; i++)
			printf("%d ", a[i]);
		printf("\n");
	}
	else
	{
		for (int j = 0; j <= M; j++)
		{
			if (b[j] == 0)			//注意  这里是b[j] 不是b[n]  仔细想一下就会知道 j 变化的次数比 n 多的多   最开始每次输出前面都不变只有后面几位会变 
			{
				a[n] = j;				//	 后面变就是因为 j 的变化引起的   n 每次递归只控制一次 
				b[j] = 1;
				sort(n + 1);
				b[j] = 0;
			}
		}
	}
}
int main()
{
	sort(0);
	return 0;
}
