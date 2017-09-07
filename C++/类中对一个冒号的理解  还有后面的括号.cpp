#include<iostream>
using namespace std;
class dong
{
public:
	dong(int a,int b):x(a),y(x),z(b)		//在声明的同时定义   相当于 x=a,y=x,z=b; 
	{}
	void print();
private:
	int x,y,z;
};
void dong::print()
{
	cout<<x<<"  "<<y<<"  "<<z<<endl;
}
int main()
{
	dong a(10,100);
	a.print();
}
