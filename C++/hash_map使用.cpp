#include <iostream> 
#include <hash_map>
#include <string>
using namespace std;

void test1(){
	__gnu_cxx::hash_map<int, string> hm;//windows下面是在 std命名空间中 
	hm[4] = "帅";
	hm[2] = "帅";
	hm[3] = "东";
	for(auto h : hm){
		cout<<h.first<<"->"<<h.second<<endl;
	}
}
/*
2->帅
3->东
4->帅
*/ 
/*
hash_map模板参数 
template <class Key, class T, class HashFcn = hash<Key>,
          class EqualKey = equal_to<Key>,
          class Alloc = alloc>
hashtable模板参数：
template <class Value, class Key, class HashFcn,
          class ExtractKey, class EqualKey,
          class Alloc>

typedef hashtable<pair<const Key, T>, Key, HashFcn,
            select1st<pair<const Key, T> >, EqualKey, Alloc> ht;
    
内置的HashFcn：
struct hash<char*>
struct hash<const char*>
struct hash<char> 
struct hash<unsigned char> 
struct hash<signed char>
struct hash<short>
struct hash<unsigned short> 
struct hash<int> 
struct hash<unsigned int>
struct hash<long> 
struct hash<unsigned long> 
内置key比较： 
struct equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x == y; }
};

注：hash_map<int, string> 等价于 hash_map<int, string, hash<int>, equal_to<int>, alloc> 
select1st 就是提取key的  map也是用的select1st
 
所以如果没有内置的hashFcn就需要自己写一个  
*/ 

//
namespace __gnu_cxx{
	template<>
	struct hash<string>{
		size_t operator()(const string &s) const { return __stl_hash_string(s.c_str()); }
		//size_t operator()(const string &s) const { return hash<const char*>()(s.c_str()); }//这个也行 不过注意模板先要实例化才能调用() 
	};
}
/* __stl_hash_string 为stl内核 const char *的hash函数 
inline size_t __stl_hash_string(const char* s){
  unsigned long h = 0; 
  for ( ; *s; ++s)
    h = 5*h + *s;
  return size_t(h);
}
struct hash<const char*>{
  size_t operator()(const char* s) const { return __stl_hash_string(s); }
};
*/
/* key = string, value = int */ 
void test2(){
	__gnu_cxx::hash_map<string, int> hm;
	++hm["帅"];
	++hm["东"];
	++hm["帅"];
	for(auto h : hm){
		cout<<h.first<<"->"<<h.second<<endl;
	}
}
/*
东->1
帅->2
*/ 
/* 上面做不是太好，毕竟太牵涉底层了 */
class HashString{
public:
	size_t operator()(const string &s) const {
		return __gnu_cxx::__stl_hash_string(s.c_str());
	}
}; 
void test3(){
	__gnu_cxx::hash_map<string, int, HashString> hm;
	++hm["帅"];
	++hm["东"];
	++hm["帅"];
	for(auto h : hm){
		cout<<h.first<<"->"<<h.second<<endl;
	}
}

/* 比较桶内的数据和key是否相等 */
/* 意义：有可能两个不同的key对应同一个桶 这时候就需要比较函数 是否需要保存新的key */
/* 现在的需求是：忽略大小写进行key比较 */ 
/* 不仅需要修改equal，hash函数也得改 */
class HashString2{
public:
	size_t operator()(const string &s) const {
		/* 忽略大小写hash->全部当成小写进行hash */ 
		int num = 0, size = s.size();
		while(size--) {
			num = 5 * num + s[size];
			if(s[size] < 'a')
				num += 'a' - 'A';
		} 
		return num; 
	}
}; 
class MyStringEqual {
public:
    bool operator()(const string &x, const string &y) const {
		int size = x.size();
		if(size != y.size())
			return false;
		cout<<x<<" compare to "<<y<<endl;
		int diff = 'a' - 'A';
		while(size--){
			if(x[size] != y[size] && 
			x[size] - diff != y[size] &&
			x[size] + diff != y[size])
				return false;
		}
		return true;
	}
};
void test4(){
	__gnu_cxx::hash_map<string, int, HashString2, MyStringEqual> hm;
	++hm["shuai"];//如果没有初始化为0 ++后变为 1 
	++hm["dong"];
	++hm["Dong"];//Dong hash结果和"dong"  一样，那么就会调用equal函数，如果不相等将采用链地址法保存 "Dong"这个key 如果相等那么将不保存"Dong" 
	++hm["DONG"];
	++hm["SHUai"];
	for(auto h : hm){
		cout<<h.first<<"->"<<h.second<<endl;
	}
}
/*
dong compare to Dong
dong compare to DONG
shuai compare to SHUai
shuai->2
dong->3
*/ 
int main(){
//	test1();
//	test2();
//	test3();
	test4();
}
