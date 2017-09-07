#include<iostream>
#include<functional>
using namespace std;
//using std::function;//函数包装

void go()
{
	cout << "go  go " << endl;
}
int add(int a, int b)
{
	return a + b;
}

void main()
{
	//		返回类型加参数
	function<void()> f = go;
	f();
	function<void()>f2 = [](){cout << "dong" << endl; };
	f2();
	function<int(int, int)> f3 = add;
	cout << f3(2, 3) << endl;



	cin.get();
}