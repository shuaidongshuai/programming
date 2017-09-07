#include<iostream>
using namespace std;
class one
{
	int c;
public:
	one(int a,int b)
	{
		c=a+b;
		cout<<c<<endl;
	}
};
int main()
{
	one d(10,10);
	return 0;
}
