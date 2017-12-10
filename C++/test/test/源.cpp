#include <iostream>
#include <string>

using namespace std;
/* 一个万用的hash Func */
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
////////////////////test///////////////////////
class A{
public:
	int a;
	char b;
	string c;
	A(int a, char b, string c) :a(a), b(b), c(c){}
	size_t HashCode() const{
		return GetHashCode(a, b, c);
	}
};
void test(){
	cout << "int(1)：" << GetHashCode(1) << endl;
	cout << "char(a)：" << GetHashCode('a') << endl;
	cout << "string(hello)：" << GetHashCode(string("hello")) << endl;
	cout << "A类：" << A(1,'a',"hello").HashCode() << endl;
}
/*
int(1)：2577477565
char(a)：2185470693
string(hello)：3990267492
A类：3971890343
*/
int main(){
	test();
	getchar();
}
