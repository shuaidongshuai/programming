#include <iostream>
/*
使用静多态来实现动多态
　　这是一种在模板元编程（Template Metaprogramming）中常见的标准编程技巧。
	在C++中，可以借助模板来实现面向对象语言所支持动多态相似的功能特性。下面是C++本身所支持动多态形式：
*/


//动多态
//class Base 
//{
//public:
//     virtual void method() = 0;
//     virtual ~Base() {}
//};
//class Derived : public Base
//{
//	public:
//		virtual void method()
//		{
//			std::cout<<"Derived"<<std::endl;
//		}
//};
//class Derived2:public Base
//{
//public:
//	virtual void method(){
//		std::cout << "Derived2" << std::endl;
//	}
//};
//int main(){ 
//    Base *pBase = new Derived;
//    pBase->method(); // 输出:"Derived"
//    delete pBase;
//    Base *pBase2 = new Derived2;
//    pBase2->method(); // 输出:"Derived2"
//    delete pBase2;
//    
//    return 0;
//}
/*
下面是使用CRTP（Curiously Recurring Template Pattern）来实现多与上面对应功能的静多态代码：
*/
template <class Derived>
class Base {
public:
	void method()
	{
		static_cast<Derived*>(this)->implementation();//用这种方式代替多态 
	}
};
class A : public Base<A> {
public:
     void implementation()
	 {
    	std::cout << "A" << std::endl;
     }
};
class B : public Base<B> {
public:
	void implementation()
	{
		std::cout << "B" << std::endl;
	}
};
int main()
{
    Base<A> *pBase = new Base<A>;
    pBase->method(); 
    delete pBase;
    
    Base<B> *pBase2 = new Base<B>;
    pBase2->method();
    delete pBase2;
    
    return 0;
}
