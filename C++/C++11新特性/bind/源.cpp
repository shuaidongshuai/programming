#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
using namespace std;

bool check_size(const string &s, string::size_type size)
{
	return s.size() >= size;
}

void test1()
{
	using namespace std::placeholders;
	auto check6 = bind(check_size, _1, 6);// _1占位符 _1为check_size的第一个参数

	cout << check6("hello World") << endl;//1
	cout << check6("dong") << endl;//0
}

void strCmpLen(string s1, string s2)
{
	cout << s1.size() << endl;
	cout << s2.size() << endl;
}

void test2()
{
	using namespace std::placeholders;
	auto slen = bind(strCmpLen, _2, _1);
	slen("hello", "dong");
	cout << typeid(slen).name() << endl;
}

int main()
{
	//test1();
	//test2();

	system("pause");
	return 0;
}