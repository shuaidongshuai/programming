#include <iostream> 
#include <bitset>
using namespace std;

#define N 10000

void isPrime(bitset<N + 1> &bit)
{
	bit[0] = bit[1] = 1;
	for (long long i = 2; i <= N; ++i)
	{
		if (bit[i] == 0)
		{
			for (long long j = i; i * j <= N; ++j)//这里需要注意 i * j 有可能是负数  所以用的是long long 
				bit[i * j] = 1;
		}
	}
}
void print(bitset<N + 1> &bit)
{
	for (int i = 0; i <= N; ++i)
		if (bit[i] == 0)
			cout << i << " ";
	cout << endl;
}
int main()
{
	bitset<N + 1> bit;
	isPrime(bit);
	print(bit);
	return 0;
}
