#include <iostream>
#include <cstring>
using namespace std;

class Dong
{
private:
	char *str;
public:
	Dong(const char *s)	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}
	//1.用&
	Dong(const Dong &d)	{
		if(&d == NULL)
			throw 0;
		str = new char[strlen(d.str) + 1];
		strcpy(str, d.str);
	}
	~Dong()	{
		delete[] str;
		str = NULL;
	}
};

int main(){
	Dong *d = NULL;
	try{
		Dong d2(*d);
	}catch(int){
		cout<<"构造参数为NULL"<<endl;
	}
	
}
