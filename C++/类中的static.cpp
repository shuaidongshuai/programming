#include<iostream>
using namespace std;
class csum
{
public:
	csum(int a=1,int b=1)
	{
		nsum+=a+b;
	}
	int get()
	{
		return nsum;
	}
	void set(int sum)
	{
		nsum=sum;
	}
private:
	 static int nsum;
};
int csum::nsum =100;
int main()
{
	csum one(9,9),two;
	cout<<one.get ()<<endl;
	cout<<two.get ()<<endl;
	two.set(5);
	cout<<one.get()<<endl;
	cout<<two.get ()<<endl;
	return 0;
}
