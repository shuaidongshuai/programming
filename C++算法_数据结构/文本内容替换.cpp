#include <iostream>
#include <string>
using namespace std;

void test(){
	string str="this is a test string.";
	string str2 = "a";
	string str3 = "dong";
	cout << str.replace(str.find(str2), str2.length(), str3) << endl;
	cout << str << endl;
}
/*
this is dong test string.
this is dong test string.
*/
void test2(){
	string str="dom nice to meet you shuai dom dom";
	string str2 = "dom";
	string str3 = "dong";
	int idx;
	while((idx = str.find(str2)) != string::npos){
		str.replace(idx, str2.size(), str3);
	}
	cout << str << endl; // dong nice to meet you shuai dong dong
}
int main (){
	test2();
	return 0;
}
