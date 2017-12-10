#include <iostream>
#include <ctime>
using namespace std;
class A{
public:
	A(){
		cout<<"a"<<endl;
	}
}; 

int main(void)
{
	char *p = "hello \0 dong";
    string s(p, 11);
    cout<<s<<endl;

    return 0;
}
