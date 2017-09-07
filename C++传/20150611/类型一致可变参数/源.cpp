#include<iostream>
#include<cstdarg>
using namespace std;

template<class T>
T add(int n, T t...)
{
	cout << typeid(T).name() << endl;
	va_list head;//typedef char *  va_list;
	va_start(head, n);//从head开始读取n个
	T res(0);//初始化为0
		for (size_t i = 0; i < n; i++)
		{
			res += va_arg(head, T);//根据数据类型取出数据
		}
	cout << res << endl;
	va_end(head);
	return res;
}

void main()
{
	cout << add(3, 1, 2, 3) << "   hello" << endl;
	cin.get();
}