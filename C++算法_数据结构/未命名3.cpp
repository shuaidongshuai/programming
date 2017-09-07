//把自然数N分解成若干个互不相同的正整数之和，使乘积最大

#include <iostream>
using namespace std;

/*找到一个数的连续正整数之和*/
int maxmul(int min, int max)
{
	int sum = 1;
	for (; min <= max; min++)
		sum *= min;
	return sum;
}
int findMaxMul(int n)
{
	int min = 0, max = 1, sum = 1;
	while(min <= n / 2)
	{
		if(sum == n)
			return maxmul(min,max);
		else if(sum > n)
		{
			sum -= min;
			++min;
		}
		else
			sum += ++max;
	}
	return 0;
}

int main()
{
	int n;
	cin>>n;
	cout<<findMaxMul(n)<<endl;
}
