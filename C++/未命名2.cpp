#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
	int arr[] = {1,2,3,4,5};
	//int *(*q)[6]= new int(*)[6];
	cout<<typeid(int(*)[6]).name()<<endl;
//	for(int i = 0;i<5;i++)
//	{
//		*(q + i) = arr + i; 
//		cout<<**(q + i)<<endl;
//	}
}
