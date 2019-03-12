#include <iostream>
using namespace std;
/*
模拟pow的部分功能
注意：1. base可能为0，如果=0 exp 就不能为负数
2. exp如果为负数，那么求出来的数要变成倒数
3. 如果出现1这样的情况那么需要一个标志（g_Invalid）看是否有问题
4. 要指出0的0次方在数学上没有意义，无论返回0还是1都能接受，下面返回的是1
*/
bool g_Invalid = false;

bool isEqual(double num1, double num2)
{
	if (num1 - num2 < 0.0000001 && num1 - num2 > -0.0000001)
		return true;
	return false;
}
/*本来计算n次方需要n次循环(每次*base)  但是如果我们计算出来了8次方，那么16次方就是8次方的结果的平方 循环次数减少了*/
double PowerWithUnsigned(double base, unsigned int exp)
{
	if (0 == exp)
		return 1;
	if (1 == exp)
		return base;
	double res = PowerWithUnsigned(base, exp >> 1);		//用 >> 1 来取代 / 2 
	res *= res;
	//判断指数是奇数还是偶数  如果是奇数还需要*base 
	if (exp & 1 == 1)									//用 & 1 来取代 % 2  
		res *= base;
	return res;
}
/*下面这样就很low
double PWU(double base,unsigned int exp)
{
double sum = 1.0;
for(int i = 0;i<exp;i++)
sum *= base;
return sum;
}
*/
double Power(double base, int exp)
{
	if (isEqual(base, 0.0) && exp < 0)
	{
		g_Invalid = true;
		return 0.0;
	}

	/*为了处理exp为负数的情况*/
	unsigned int absExp = (unsigned int)exp;
	if (exp < 0)
		absExp = (unsigned int)-exp;

	//下面用一个高效算法
	double res = PowerWithUnsigned(base, absExp);

	if (exp < 0)
		res = 1.0 / res;
	return res;
}


int main()
{
	cout << Power(5.0, 3) << endl;
	cout << Power(5.0, 0) << endl;
	cout << Power(0, 0) << endl;
	cout << Power(-3, 3) << endl;
	cout << Power(-1.2, 2) << endl;
	cout << Power(-3, -1) << endl;
	double res = Power(0, -1);
	if (g_Invalid)
		cout << "有问题" << endl;
	else
		cout << res << endl;
	return 0;
}
