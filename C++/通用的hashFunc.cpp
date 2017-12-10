#include <iostream>
#include <string>
using namespace std;
/* 一个万用的hash Func */
namespace dong{
template<typename T>
inline void HashCode(size_t &seed, const T& val){
	seed ^= std::hash<T>()(val)+0x9e3779b9 + (seed << 6) + (seed >> 2);
}
template<typename T>
inline void GetHashCode(size_t &seed, T& val){
	HashCode(seed, val);
}
template<typename T, typename... Types>
inline void GetHashCode(size_t &seed, T& val, const Types&... args){
	HashCode(seed, val);
	GetHashCode(seed, args...);
}
template<typename... Types>
inline size_t GetHashCode(const Types&... args){
	size_t seed = 0;
	GetHashCode(seed, args...);
	return seed;
}
}
////////////////////test///////////////////////
class A{
public:
	int a;
	char b;
	string c;
	A(int a, char b, string c) :a(a), b(b), c(c){}
	size_t HashCode() const{
		return dong::GetHashCode(a, b, c);
	}
};
void test(){
	cout << "int(1)：" << dong::GetHashCode(1) << endl;
	cout << "char(a)：" << dong::GetHashCode('a') << endl;
	cout << "string(hello)：" << dong::GetHashCode(string("hello")) << endl;
	cout << "A类：" << A(1,'a',"hello").HashCode() << endl;
}
/*
int(1)：2654435770
char(a)：2654435866
string(hello)：2762169581789623169
A类：2762181016555499807
*/ 
int main(){
	test();
}

