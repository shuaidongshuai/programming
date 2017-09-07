#include<iostream>
using namespace std;
class dong
{
public:
	dong(int date=0)
	{

		data=date;
	}
	int get()
	{
		return data;
	}
private:
	int data;
};
int main()
{
	dong a(3);
	dong b(a);
	cout<<a.get()<<endl;
	cout<<b.get()<<endl;
}
