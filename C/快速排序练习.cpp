//再来敲一次快速
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void quick(int a[], int left, int right)
{
	int l = left, r = right;
	if (l < r)
	{
		int t = a[l];
		while (l < r)
		{
			while (l < r && a[r] >= t)
				r--;
			a[l] = a[r];
			while (l < r && a[l] < t)
				l++;
			a[r] = a[l];
		}
		a[l] = t;
		quick(a, left, l - 1);
		quick(a, l + 1, right);
	}
}
/*
	while (l < r && a[r--] >= t)
			a[l] = a[++r];			//不能这样写，，以前一直不知道原因，，其实就是因为 l < r &&  也就是说r--不一定每次循环都执行得到  
									//也不能把  l < r 去掉  原因：我们a[l] = a[r] 就是为了把右边大的放到左边来  如果不保证l<r的话就会乱 
									//// 把 l < r 放到a[r] >= t 后面又会导致， l < r 比较不准确，此时的 r 是 r - 1 
*/

int main()
{
	int i, a[80];
	srand(time(NULL));
	for (i = 0; i<80; i++)
	{
		a[i] = rand() % 100;
		printf("%d\t", a[i]);
	}
	quick(a, 0, 79);
	printf("\n排序后：\n");
	for (i = 0; i<80; i++)
		printf("%d\t", a[i]);
}
