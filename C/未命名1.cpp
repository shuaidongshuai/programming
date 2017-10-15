#include <iostream>
#include <string>
using namespace std;

class A{
public:
	string s = "hello";
	void show(){cout<<s<<endl;}
};
A test(){ A(); }
int main(){
	string str("hello dong");
	for(auto c : str)
		cout<<c;
}
