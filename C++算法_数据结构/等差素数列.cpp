/*
等差素数列
2,3,5,7,11,13,....是素数序列。
类似：7,37,67,97,127,157 这样完全由素数组成的等差数列，叫等差素数数列。
上边的数列公差为30，长度为6。

2004年，格林与华人陶哲轩合作证明了：存在任意长度的素数等差数列。
这是数论领域一项惊人的成果！

有这一理论为基础，请你借助手中的计算机，满怀信心地搜索：

长度为10的等差素数列，其公差最小值是多少？
*/

#include <iostream> 
#include <bitset>
using namespace std;
#define N 10000
long long arr[N / 2];//用来存储素数，空间换时间
int len;
void isPrime(bitset<N + 1> &bit)
{
	bit[0] = bit[1] = 1;
	for (long long i = 2; i <= N; ++i)
	{
		if (bit[i] == 0)
		{
			for (long long j = i; i * j <= N; ++j)//这里需要注意 i * j 有可能是负数  所以用的是long long 
				bit[i * j] = 1;
			arr[len++] = i;
		}
	}
}
int result()
{
	bitset<N + 1> bit;
	
	isPrime(bit);

	for (int i = 210; i <= 1000; ++i)//公差 
	{
		for (int j = 0; j < len; ++j)//遍历素数 
		{
			int su = arr[j];
			if (su == 199)
				cout << su << endl;
			int k = 1;
			for (; k < 10; ++k)//对每一个素数判断是否满足条件
				if (k * i + su >= N || bit[k * i + su] == 1)
					break;
			if (k == 10)
				return i;
		}
	}
	return 0;
}
int main()
{
	cout << result() << endl;

	return 0;
}
