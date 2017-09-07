#include <iostream>
using namespace std;

#define product(x) (x*x)

int main()
{
	int i = 3,j,k;
	j = product(i++);
	k = product(++i);
	cout<<j<<endl;
	cout<<k<<endl;
	return 0;
}
/*
这题在不同的编译器会有不同的结果：
第一种情况:
j = (i++*i++);=>3*4  
k = (++i*++i);=>6*7  
 
j=(i++*i++)=>3*3 
k = (++i*++i);=>7*7  
 
j=(i++*i++)=>3*3
毕竟加了2次
k = (++i*++i);=>5*5 
终值7
*/
