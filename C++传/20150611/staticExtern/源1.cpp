#include<iostream>
int a = 100;
static int x = 100;
namespace
{
	int x = 1;
}

using namespace std;
void test()
{
	cout << ::x << endl;
}