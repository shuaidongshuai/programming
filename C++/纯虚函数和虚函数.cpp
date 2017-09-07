#include <iostream>
using namespace std;
class Chen{
	public:
		virtual void test();			//虚函数，派生类 不需要实现它(可以覆盖)，但是 基类必须实现它 
		virtual void test2() = 0;		//纯虚函数，派生类 必须实现它（必须覆盖），但是 基类不需要实现它
};
void Chen::test(){
	cout<<"chen"<<endl;
}
class Ming:public Chen{
	public:
		void test() override{
			cout<<"ming"<<endl;
		}
		void test2() override{
			cout<<"ming2"<<endl;
		}
};
int main()
{
	Ming ming;
	ming.test();
	ming.test2();
}
