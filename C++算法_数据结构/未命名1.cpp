#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cstring> 
using namespace std;

//第一种C风格的转化(以前一直喜欢的  sprintf 功能强大)
void test()
{
	char *s = "dong";
	int a = 52;
	float b = .1314;
	char *buf = new char[strlen(s) + sizeof(a) + 1];
	sprintf(buf, "%s%d%.4f", s, a, b);
	printf("%s\n", buf);
}
//半C半C++风格
void test1()
{
	string s = "dong";
	int a = 520;
	char *buf = new char[10];//2147483647 int最大值
	_itoa(a, buf, 10);		//itoa虽然可以转化为各种进制，但是注意不能是float或者double
	cout << s + buf << " | ";
	_itoa(a, buf, 16);
	cout << s + buf << endl;
}
//纯C++风格
void test2()
{
	string s = "陈明东";
	int a = 52;
	double b = .1314;
	ostringstream oss;
	oss << s << a << b;
	cout << oss.str() << endl;
}
//C++11新特性
void test3()
{
	int a = 520;
	float b = 5.20;
	string str = "dong";
	string res = str + to_string(a);
    cout << res << endl;
    res = str + to_string(b);
    res.resize(8);
    cout << res << endl;
}
int main()
{
	test();
	test1();
	test2();
	test3();
	return 0;
}
