//C++中虚拟继承的概念
//为了解决从不同途径继承来的同名的数据成员在内存中有不同的拷贝造成数据不一致问题，
//将共同基类设置为虚基类。这时从不同的路径继承过来的同名数据成员在内存中就只有一个拷贝，
//同一个函数名也只有一个映射。这样不仅就解决了二义性问题，也节省了内存，避免了数据不一致的问题。

//-----------------------------------------------------
//名称：blog_virtual_inherit.cpp 
//说明：C++虚拟继承学习演示 
//环境：VS2005 
//blog：pppboy.blog.163.com 
//---------------------------------------------------- 
#include <iostream>
using namespace std;

class dong{
	public:
	void print(){cout << "dong  dong" <<endl;}
};

 //Base 
 class Base:virtual public dong
 {
 };

 //Sub 
 class Sub:virtual public dong //虚继承dong 
 {
 };

 //Child 
 class Child : public Base , public Sub //虚继承dong
 {
 };

class Child2:public Base,public Sub{
};

 int main(int argc, char* argv[])
 {
 Child c;

 //不能这样使用，会产生二意性，VC下error C2385 
 //c.print();  

 //只能这样使用 
 c.Base::print();
 c.Sub::print();
 
 cout<<"------------------"<<endl;
 
 Child2 cc;
 cc.print();//这里就可以直接调用 

 system("pause");
 return 0;
 }
