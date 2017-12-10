#include <iostream>
#include <map>
#include <ctime>
using namespace std;
#define N 5000000
void test1(){
	map<int, int> m;
	for(int i = 0; i < N; ++i){
		m[i] = i;
	}
}
void test2(){
	map<int, int> m;
	for(int i = 0; i < N; ++i){
		m.insert(make_pair(i,i));
	}
}
int main() {
	string s1,s2,s3; 
	to_string(s1,10.5);//doubleµ½string
	to_string(s2,123);//intµ½string
	to_string(s3,true);//boolµ½string
	cout<<s1<<endl;
	cout<<s2<<endl;
	cout<<s3<<endl;
}
