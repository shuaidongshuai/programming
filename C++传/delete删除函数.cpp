#include <iostream>
using namespace std;

//声明函数  = delete;就是删除这个函数 
void show(char a) = delete; //加了这句话，，就不能用 show('A');了 
void show(int i)
{
	cout<<i<<endl;
}

int main()
{
	//show('A');//结果是 65 
	show(1);
}
