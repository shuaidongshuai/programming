#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int test1()
{
	//1
	string str1 = "56";
	cout << typeid(str1.c_str()).name() << endl;//char const *
	char *s1 = (char *)str1.c_str();
	*s1 = '9';
	cout << str1 << endl;//96		修改char *		string	也要跟着变

	//2
	string str2 = "99";
	const char *s2 = str2.c_str();
	str2 = "hello";
	cout << s2 << endl;//hello		修改string    const char * 也要跟着变  
	//s2最后指向的内容是垃圾,因为s对象被析构,其内容被处理,而且const char * 内容被修改，并不是一件好事

	//第一种情况没办法，编译器都告诉你是const的，你非要强转，说明你自己知道自己在干什么
	//对于第二种情况我们可以用strcpy来防止出错
	char s3[100];
	strcpy_s(s3, str2.c_str());//这样才不会出错,c_str()返回的是一个临时指针,不能对其进行操作

	return 0;
}
int main()
{
	string s = "7";
	char * ss = "hello";
	cout << s + ss << endl;

	//为了实现java中的  string s = 4 + "";//C++中不能这样搞
	char s2 = '0' + 4;
	cout << s2 << endl;

	system("pause");
	return 0;
}