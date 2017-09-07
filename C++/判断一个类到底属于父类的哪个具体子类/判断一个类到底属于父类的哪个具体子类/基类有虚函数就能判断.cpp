#include <iostream>
using namespace std;

/*
运行时类型识别RTTI的特点如下：
（1）可以通过父类指针识别其所指向对象的真实数据类型
（2）RTTI必须建立在虚函数的基础上
（3）
Movable * p = new Bus();
cout<<typeid(*p).name()<<endl;//打印结果为Bus，返回指针指向的对象的类型
cout<<typeid(p).name()<<endl;//打印结果为Movable,返回指针本身的类型
(4)  Movable * obj;
Bus bus = dynamic_cast<Bus&>(*obj);//正确
Bus bus = dynamic_cast<Bus*>(obj);//正确
Bus bus = dynamic_cast<Bus>(*obj);//错误，错误详细信息如下：

dynamic_cast的使用说明：
（1）只能有用于指针和引用的转换，将父类指针或引用转换为子类指针和引用
（2）要转换的类型中必须包含虚函数
（3）如果转换成功，返回的就是子类的地址，如果转换失败，返回NULL
*/

class D1;
class D2;

class B
{
public:
	virtual void test()			//必须有一个虚函数  构建多态
	{
	}
	static void dong(B* b)
	{
		if (typeid(*b).name() == typeid(D1).name())
		{
			cout << "这是D1类对象" << endl;
		}
		else if (typeid(*b).name() == typeid(D2).name())
		{
			cout << "这是D2类对象" << endl;
		}
	}
};
class D1 : public B
{};
class D2 : public B
{};
int main()
{
	B* b1 = new D1;
	B* b2 = new D2;
	cout << typeid(b1).name() << endl;//class B *			指针是 B* 类型
	cout << typeid(*b1).name() << endl;//class D1			但是他指向的是D1的，*b1就是class D1的
	cout << typeid(*b2).name() << endl;

	B::dong(b1);
	B::dong(b2);

	system("pause");
	return 0;
}
/*
、、、、、、、、、、、条件就是 基类必须有一个虚函数

class B *
class D1
这是D1类对象
这是D2类对象
*/