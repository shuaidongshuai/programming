/*
如果一个自然数N的K进制表示中任意的相邻的两位都不是相邻的数字，那么我们就说这个数是K好数。
求L位K进制数中K好数的数目。
例如K = 4，L = 2的时候，
所有K好数为11、13、20、22、30、31、33 共7个。由于这个数目很大，请你输出它对1000000007取模后的值。

输入格式
输入包含两个正整数，K和L。

输出格式
输出一个整数，表示答案对1000000007取模后的值。
样例输入
4 2
样例输出
7
******************简单DP，dp[i][j],其中i代表的是数字有几位，j代表首位放j的情况有几种*************************** 
*/
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int k, l, **dp,sum = 0;
	cin >> k >> l;//k进制，l位
	/* 下面是初始化 */
	dp = new int*[l + 1];
	for (int i = 0; i <= l; i++)
		dp[i] = new int[k];
	for (int i = 0; i<k; i++)
		dp[1][i] = 1;
	for (int i = 2; i <= l; i++)
		memset(dp[i], 0, 4*k);

	for (int i = 2; i <= l; i++)		//  当前是i位数 
	{
		for (int add = 0; add<k; add++)	//add就是将要在前面加上的数，比如 21	add = 6 就变成了 621 
		{
			for (int j = 0; j<k; j++)	//	遍历前面j开头的数 
			{
				if (add != j + 1 && add != j - 1)
				{
					dp[i][add] += dp[i - 1][j];	//加上  i-1位，最高位为add(刚加的)，k好数个数
					dp[i][add] %= 1000000007;
				}
			}
		}
	}
	for (int i = 1; i < k; i++)//为什么从1开始？ 答：最高位不能为0 
	{
		sum += dp[l][i];
		sum %= 1000000007;
	}
	
	////////////////////////下面代码可以不看////////////////////////// 
	for (int i = 1; i <= l; i++)
	{
		for (int j = 0; j<k; j++)
			cout << "|" << dp[i][j];
		cout<< "|" << endl;
	}
	for(int i = 1;i<k;i++)
	{
		cout<<dp[l][i];
		if(i == k - 1)
		{
			cout<<" = "<<sum<<endl;
		}
		else
			cout<<" + ";
	}
	return 0;
}
