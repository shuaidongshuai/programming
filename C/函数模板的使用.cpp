#include<iostream>
using namespace std;
template<class t>t add(t a,t b)
{
	return a+b;
 } 
 int main()
 {
 	cout<<add(10.2,10.0)<<endl;		//里面的两个数只能是相同类型，如int int或者double double或者char char 
 	cout<<add('a','\4')<<endl;		//   \4就是按字母表往后移动4位 
 	return 0;
 }
