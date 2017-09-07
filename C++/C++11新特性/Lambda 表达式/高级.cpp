#include<iostream>
#include<algorithm>
#include<array>

using namespace std;

void main()
{
	array<int, 5> arr = { 1, 2, 3, 4, 5 };
	for_each(arr.begin(), arr.end(), [](int num){cout << num << endl; });

	cin.get();
}


void main7()
{
	int a = 10;
	int b = 9;
	int c = 8;
	[&a, b, c](){a = 100; cout << a << " " << b << "  " << c << endl; }();//a可读可写。bc只读
	cout << a << " " << b << "  " << c << endl;

	cin.get();
}


void main6()
{
	int n1 = 10;
	int n2 = 20;

	[=](){cout << n1 << "  " << n2 << endl; }();// = 代表捕获外部变量。。但是。只能读n1 n2 不能改变外部变量的值
	[=]()mutable{n1 = 500, n2 = 400; cout << n1 << "  " << n2 << endl; }();//加了mutable就可以用外部变量。但是里面的n1 n2是副本

	[&](){cout << n1 << "  " << n2 << endl; }();//
	[&](){n1 = 100, n2 = 200; cout << n1 << "  " << n2 << endl; }();// & 既可以访问外部变量。也可以修改外部变量 你
	cout << n1 << "   " << n2 << endl;


	cin.get();
}

