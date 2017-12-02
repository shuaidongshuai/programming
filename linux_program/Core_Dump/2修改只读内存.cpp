#include <iostream>
#include <vector>
using namespace std;

void test(char *p){
	*(p + 5) = 'a';
}

int main()
{
	char *p = "hello";
	test(p);
}
