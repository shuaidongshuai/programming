#include <iostream>
using namespace std;

int main()
{
	int a = 0, b =  0x7fffffff;
	int mid = ( a + b) / 2;					//不安全 
	int mid2 = (b - a) / 2 + a; 			//安全 
	
	cout<<mid<<endl;
	cout<<mid2<<endl;
	
	/////////////////////////////////////////////////////////// 
	a = 1, b =  0x7fffffff;
	mid = ( a + b) / 2;
	mid2 = (b - a) / 2 + a; 
	
	cout<<mid<<endl;//数组越界 
	cout<<mid2<<endl;
	
	return 0;
}
