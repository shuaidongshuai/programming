#include<iostream>
#include<cstring>
using namespace std;
class dong
{
public:
	dong(char *p)
	{
		str=(char *)new char[strlen(p)+1];
		strcpy(str,p);
	}
	char *get()
	{
		return str;
	}
private:
	char *str;
};
int main()
{
	dong a("hello");
	dong b(a);
	cout<<a.get()<<endl<<b.get ()<<endl;
	return 0;
}
