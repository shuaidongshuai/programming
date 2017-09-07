#include <iostream>
using namespace std; 


int main1()
{
	int a = 10;
	int aa = 100;
	const int b = a;//c++不会在这里做任何优化。。因为a是变量
	
	cout<<b<<endl;
	a = 20;
	cout<<b<<endl;
	
	int* p = (int*)&b;
	*p = 20;
	cout<<b<<endl; 
	return 0;
}

int main()  
{  
    const volatile int i = 10;  //volatile的作用是： 作为指令关键字，确保本条指令不会因编译器的优化而省略，且要求每次直接读值.
    int* pi = (int*)(&i);  
    *pi = 100;  
    printf("*pi: %d\n",*pi);  
    printf("i: %d\n",i);  
    printf("pi: %p\n",pi);  
    printf("&i: %p\n", &i);  
    return 0;  
}  
