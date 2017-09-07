//小易有一个圆心在坐标原点的圆，小易知道圆的半径的平方。小易认为在圆上的点而且横纵坐标都是整数的点是优雅的，小易现在想寻找一个算法计算出优雅的点的个数，请你来帮帮他。
//例如：半径的平方如果为25
//优雅的点就有：(+/ -3, +/ -4), (+/ -4, +/ -3), (0, +/ -5) (+/ -5, 0)，一共12个点。
//输入描述 :
//输入为一个整数，即为圆半径的平方, 范围在32位int范围内。
//
//
//输出描述 :
//输出为一个整数，即为优雅的点的个数

#include<iostream>
#include<cmath>
using namespace std;

//case通过率为100.00%
int main()
{
	int r2, sum = 0;
	cin >> r2;
	int r = sqrt(r2);//这是一个省略小数的半径
	if (r2 == r*r)
		sum = 4;
	int jj = r;//优化用的变量，不必要每次都从r开始
	for (int i = 1; i <= r; i++)
	{
		for (int j = jj; j > 0; j--)
		{
			int len2 = i*i + j*j;
			if (len2 == r2)
			{
				sum+=4;
				jj = j;
				break;
			}
			if (len2 < r2)
				break;
		}
	}
	cout << sum << endl;
	system("pause");
	return  0;
}
//通过率80%
int main3()
{
	int r2, sum = 0;
	cin >> r2;
	int r = sqrt(r2);//这是一个省略小数的半径
	for (int i = -r; i <= r; i++)
	{
		for (int j = r; j >=0; j--)
		{
			if (i*i + j*j == r2)
			{
				sum++;
				if (j != 0)
					sum++;
				break;//如果找到一个那么不可能在这个y轴再出现了
			}
		}
	}
	cout << sum << endl;

	system("pause");
	return  0;
}
//通过率80%
int main2()
{
	int r2, sum = 0;
	cin >> r2;
	int r = sqrt(r2);//这是一个省略小数的半径
	for (int i = -r; i <= r; i++)
	{
		for (int j = 0; j <= r; j++)
		{
			if (i*i + j*j == r2)
			{
				sum++;
				if (j != 0)
					sum++;
			}
		}
	}
	cout << sum << endl;

	system("pause");
	return  0;
}

//通过率  70%
int main1()
{
	int r2, sum = 0;
	cin >> r2;
	int r = sqrt(r2);//这是一个省略小数的半径
	for (int i = -r; i <= r; i++)
	{
		for (int j = -r; j <= r; j++)
		{
			if (i*i + j*j == r2)
				sum++;
		}
	}
	cout << sum << endl;

	system("pause");
	return  0;
}