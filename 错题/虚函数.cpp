#include<iostream>
using namespace std;
class Base
{
public:
    Base()
    {
        Init();
    }
    virtual void Init()
    {
        printf("Base Init\n");
    }
    void func()
    {
        printf("Base func\n");
    }
};
class Derived: public Base
{
public:
    virtual void Init()
    {
        printf("Derived Init\n");
    }
    void func()
    {
        printf("Derived func\n");
    }
};
 
int main()
{
    Derived d;
    ((Base *)&d)->func();
    ///////////////////////////////////////////
    cout<<"------------测试--------------"<<endl;
	Derived *dd = new Derived;//注意初始化父类的时候，和子类没有任何关系 
	((Base *)dd)->func(); 
    return 0;
}
