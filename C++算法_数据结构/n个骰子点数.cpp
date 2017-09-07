#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

#define M 6 
/*
n个骰子所有朝上一面的点数和为s
输出：s所有可能的值的概率

思路：求出每个值出现的次数 除以 6 ^ n
*/
// 递归加hash求出所有s出现的次数
void probability(int number, int count, int sum, int *numCount)
{
	if (count == 0)
	{
		++numCount[sum - number];
		return;
	}
	/*这个骰子当前取值 1 - M */
	for (int i = 1; i <= M; ++i)
		probability(number, count - 1, sum + i, numCount);
}
void printProbability(int num)
{
	if (num < 1) return;
	int maxVal = num * M;
	int *numCount = new int[maxVal - num + 1]();	//节约一点内存 beacause:最小值是num

	//递归把numCount填满
	probability(num, num, 0, numCount);

	int total = pow(M, num);
	for (int i = 0; i < maxVal - num + 1; ++i)
	{
		double ratio = (double)numCount[i] / total;
		cout << i + num << " 出现的概率：" << ratio << endl;
	}
	delete numCount;
}
/* 非递归  递推的过程 */
/* 利用n个数和为s的个数   ==   n-1个数和为(s-1)(s-2)(s-3)(s-4)(s-5)(s-6) 之和 */ 
void PrintProbability2(int num)
{
	if (num < 1) return;
	int maxVal = num * M;
	/* 因为只用到了n个数和n-1个数 所以两个数组轮流来用就好了*/
	int *numCount[2];
	numCount[0] = new int[maxVal + 1];
	numCount[1] = new int[maxVal + 1];
	/* 初始化很重要 因为后面都是当做0直接累加的 */
	memset(numCount[0], 0, (maxVal + 1) * sizeof(int));
	memset(numCount[1], 0, (maxVal + 1) * sizeof(int));

	int flag = 0;	/* n = 1 时用【0】号数组 */
	for (int i = 1; i <= M; ++i)
		numCount[flag][i] = 1;

	/* 上面已经初始化好了 n = 1 的情况 下面解决 n > 1 的情况(递推) */
	for (int i = 2; i <= num; ++i)
	{
		/* n = i 时 最小值是 i，最大值是 i * M */
		for (int j = i; j <= i * M; ++j)
		{
			/* i个数，和为j出现的次数 == i - 1个数和为 (j - 1)  (j - 2)  (j - 3)  (j - 4)  (j - 5)  (j - 6) 之和 */
			for (int k = 1; k <= M && k <= j; ++k)
				numCount[1 - flag][j] += numCount[flag][j - k];
		}
		/* 下次要换数组，先把这个数组清空 */
		memset(numCount[flag], 0, i * M * sizeof(int));
		/* 两个数组轮流来当前一个数 */
		flag = 1 - flag;
	}

	int total = pow(M, num);
	for (int i = num; i < maxVal + 1; ++i)
	{
		double ratio = (double)numCount[flag][i] / total;
		cout << i << " 出现的概率：" << ratio << endl;
	}
	delete numCount[0];
	delete numCount[1];
}

int main()
{
	printProbability(4);
	cout << "---------------------" << endl;
	PrintProbability2(4);

	system("pause");
}
