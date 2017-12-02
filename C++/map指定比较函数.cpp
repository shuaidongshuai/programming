#include <iostream>
#include <map> 
#include <string>
using namespace std;

//其实 greater<int>() 就是一个仿函数而已 

class MyCompare{
public:
	bool operator()(const string &s1, const string &s2){
		if (s1.length() < s2.length())
			return false;
		else if (s1.length() > s2.length())
			return true;
		else{
			return s1 < s2;
		}
	}
};
void test(){
	map<string, int, MyCompare> mp;
	mp["d"] = 1;
	mp["chen"] = 1;
	mp["ming"] = 1;
	mp["shuai"] = 1;
	for (auto m : mp){
		cout << m.first << " -> " << m.second << endl;
	}
}
/////////////重载<也可以/////////////////////////////
class Dong{
public:
	int a;
	string str;
	Dong(int a, string str) :a(a), str(str){}
	bool operator< (const Dong &d) const{//两个const不能省略，调用的时候是调用const类型
		return a < d.a;
	}
};
void test2(){
	map<Dong, int> mp;
	mp[Dong(2,"ming")] = 1;
	mp[Dong(3, "dong")] = 1;
	mp[Dong(1, "chen")] = 1;
	++mp[Dong(3, "dong")];
	for (auto m : mp){
		cout << m.first.str << " -> " << m.second << endl;
	}
}
int main(){
	test();
	cout << "--------------" << endl;
	test2();
}
