#include <iostream>
using namespace std;

class A{
	public: 
	~A()
	{
		cout<<"A析构函数"<<endl;
	}
};

class C{
	public: 
	virtual ~C()					//是为了当用一个基类的指针删除一个派生类的对象时，派生类的析构函数会被调用。
	{
		cout<<"C析构函数"<<endl;
	}
};

class B:public A,public C{
	public: 
	~B()
	{
		cout<<"B析构函数"<<endl;
	}
};

void Del1(A* a)
{
	delete a;
 }
void Del2(C* c)
{
	delete c;//基类的指针删除一个派生类的对象，派生类的析构函数会被调用。
}

int main1()
{
	B* b = new B;
	Del1(b);
	cout<<"--------------"<<endl;
	B* bb = new B;
	cout<<"--------------"<<endl;
	Del2(bb);							//结论和上面差那么多，就是因为：C中有虚析构函数。。会吧所有继承的基类子类的析构函数都执行一次 
	cout<<"--------------"<<endl;
//	B析构函数
//	A析构函数
 } 
 
 //下面  看着会更简单， 
 class D : public C{
 	public:
	 ~D(){
	 	cout<<"D析构函数"<<endl;
	 } 
 }; 
 int main()
 {
 	D* d = new D;
 	Del2(d);
	cout<<"--------------"<<endl; 	
 	C* c = new D();
 	delete c;
  } 
