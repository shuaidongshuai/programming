//重写override：也叫做覆盖。子类重新定义父类中有相同名称和参数的虚函数。函数特征相同。但是具体实现不同，主要是在继承关系中出现的 。
//重写需要注意：
//1 被重写的函数不能是static的。必须是virtual的
//2 重写函数必须有相同的类型，名称和参数列表
//3 重写函数的访问修饰符可以不同。尽管virtual是private的，派生类中重写改写为public,protected也是可以的
//
//重定义 (redefining)也叫做隐藏:
//
//子类重新定义父类中有相同名称的非虚函数 ( 参数列表可以不同 ) 。
//
//如果一个类，存在和父类相同的函数，那么，这个类将会覆盖其父类的方法，除非你在调用的时候，强制转换为父类类型，否则试图对子类和父类做类似重载的调用是不能成功的。 
#include <iostream> 
using namespace std;
//基类 
class Base {
 virtual void display() { cout<<"Base display()"<<endl; }
 void say(){ cout<<"Base say()"<<endl; }
public:
 void exec(){ display(); say(); }
 virtual void f1(string a) { cout<<"Base f1(string)"<<endl; }
 void f1(int a) { cout<<"Base f1(int)"<<endl; } //overload，两个f1函数在Base类的内部被重载
};
//A
class DeriveA:public Base{
public:
 void display() { cout<<"DeriveA display()"<<endl; } //override，基类中display为虚函数，故此处为重写
 void f1(int a,int b) { cout<<"DeriveA f1(int,int)"<<endl; } //redefining，f1函数在Base类中不为虚函数，故此处为重定义
 void say() { cout<<"DeriveA say()"<<endl; } //redefining，同上
};
//B
class DeriveB:public Base
{
public:
	void f1(int a) { cout<<"DeriveB f1(int)"<<endl; } //redefining，重定义]
	void f1(string a){ cout<<"DeriveB f1(string)"<<endl; }
};

int main()
{
	DeriveB b;
 	Base *base=&b;
 	
 	b.f1(1);	
 	//DeriveB f1(int)		
 	base->f1(1);
 	//Base f1(int)			//子类“重定义”了父类的方法，父类的方法只是被隐藏了。。强制类型转化为基类，调用的仍然是基类的方法
 
 	
	b.f1("1");
	//DeriveB f1(string)	
	base->f1("1"); 			
	//DeriveB f1(string)	//子类“重载”了父类的方法，父类的方法被改变了。。强制类型转化为基类，调用的仍然是基类的方法
}

int main1(){
 DeriveA a;
 Base *base=&a;
 base->exec();
// DeriveA display()
// Base say() 
 // base里边的函数display被A类覆盖，但是say还是自己的。A类只是 重定义(隐藏)了基类的方法 
 a.exec(); //same result as last statement声明 
 // DeriveA display()
// Base say()

 a.say();
 // DeriveA say()
 
 DeriveB b;
 b.f1(1); //version of DeriveB called
// DeriveB f1(int)
}
// 综上所述，总结如下：
//1 成员函数“重载”特征：
//   a 相同的范围（在同一个类中）
//   b 函数名字相同
//   c 参数不同
//   d virtual关键字可有可无
//2 “重写”（覆盖)是指派生类函数覆盖基类函数，特征是：（当强制转化为基类时，不能调用基类的函数，只能调用被重写的函数）
//   a 不同的范围，分别位于基类和派生类中
//   b 函数的名字相同
//   c 参数相同
//   d 基类函数必须有virtual关键字
//3 重定义(隐藏)是指派生类的函数屏蔽了与其同名的基类函数，规则如下：
//   a 如果派生类的函数和基类的函数同名，但是参数不同，此时，不管有无virtual，基类的函数被隐藏。（当强制转化为基类时，还能调用基类的函数） 
//   b 如果派生类的函数与基类的函数同名，并且参数也相同，但是基类函数没有vitual关键字，此时，基类的函数被隐藏。
