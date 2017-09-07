#include <iostream>
using namespace std;

//#define语句中的#是把参数字符串化，##是连接两个参数成为一个整体。
 
#define Str(A) #A		//这样可以把任何变量名转化为字符串

#define Cat(A,B) A##B()
#define Cat2(A,B) A##B

class Dong
{
public:
	void test()
	{
		cout<<"test"<<endl;
	}
	void test2()
	{
		cout<<"test2"<<endl;
	}
	void testYou()
	{
		cout<<"testYou"<<endl;
	}
};
int main()
{
	Dong dong;
	cout<<Str(dong)<<endl;	//任何变量名转化为字符串
	
	Cat(dong.test,You);
	Cat(dong.test,2);
	Cat(dong.test,);
	
	
	
	
}
