#include <iostream>
#include <cstddef>
using namespace std;

/*
int &dd  就等价于  int * const dd 

不过 引用不能指向空   int* const dd 可以指向空 
*/
int main()
{
	int d = 10;
	int e = 20;
	
	int &dd = d;
	int * const dd2 = NULL;

	//int &dd = NULL;
	
//	*dd2 = e;
//	dd = e;
//	
//	cout<<dd<<endl;
//	cout<<*dd2<<endl;
	
}
/*

*/
