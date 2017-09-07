#include <iostream>
using namespace std;  

int gFlag = 0;  

class Base  
{
public:  
Base(){cout << "Base called : " << gFlag++ << endl;}  
void print(){cout << "Base print" <<endl;}  
};

class Mid1 : virtual public Base  						//虚继承 
{
public:  
Mid1(){cout << "Mid1 called" << endl;}  
private:  
};

class Mid2 : virtual public Base  						// 虚继承 
{
public:  
Mid2(){cout << "Mid2 called" << endl;}  
};

class Child:public Mid1, public Mid2  					// 这里不用虚继承也行 
{
public:  
Child(){cout << "Child called" << endl;}  
};

int main(int argc, char* argv[])  
{
Child d;

//这里可以这样使用  
d.print();

//也可以这样使用  
d.Mid1::print();
d.Mid2::print();

system("pause");  
return 0;  
}
