//以阻止对象继承、方法重载

class Base final
{
};
class Derived : public Base //继承密闭类，语法错误
{
};

//final方法

class Base2
{
	virtual void A() final;
};
class Derived : public Base2
{
	virtual void A(); //重写密闭方法，编译出错
};

int main()
{

}