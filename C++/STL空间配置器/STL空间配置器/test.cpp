#include <iostream>
#include "yhp_alloc.h"
using namespace std;
using namespace yhp;

int main()
{
	int *arr = simple_alloc<int, alloc>::allocate(1);		//8
	int *arr2 = simple_alloc<int, alloc>::allocate(3);	//12

	
	system("pause");
	return 0;
}