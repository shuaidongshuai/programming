#include <iostream>
#include "MemPool.h"
using namespace std;

int main()
{
	MemPool<int> *pool = new MemPool<int>(1);


	system("pause");
	return 0;
}
