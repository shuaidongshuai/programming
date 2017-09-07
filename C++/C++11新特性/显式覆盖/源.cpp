class Base
{
	virtual void A(float = 0.0);
	virtual void B() const;
	virtual void C();
	void D();
};
class Derived : public Base
{
	virtual void A(int = 0) override; //定义不一致，编译错误
	virtual void B() override;        //返回类型不是const，编译错误
	virtual void C() override;        //正确
	void D() override;                //不是虚函数，编译错误
};
