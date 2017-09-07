#include <iostream>
using namespace std;

// 要求用宏定义求一个结构体中遍历的相对偏移量
#define FIND(Dstruct,e) (int *)&((Dstruct *)0)->e

struct Dstr
{
	int a;
	char c;
	double b;
};

int main()
{
	cout<< FIND(struct Dstr,a) <<endl;
	cout<< FIND(struct Dstr,c) <<endl;
	cout<< FIND(struct Dstr,b) <<endl;
}

