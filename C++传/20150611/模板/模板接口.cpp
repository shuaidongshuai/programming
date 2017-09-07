#include<iostream>
using namespace std;

void show(int num)
{
	cout << num << endl;
}

//泛型接口，任何数据类型，传递任何函数指针都可以
template<class T,class F>
void run(T t, F f)
{
	f(t);
}

template<class T>
void show2(T t)
{
	cout << t << endl;
}
void main()
{
	//run(520, show);
	run(520, show2<int>);
	run("love", show2<const char *>);

	cin.get();
}