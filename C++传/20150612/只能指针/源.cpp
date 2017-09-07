#include<iostream>
#include<windows.h>
#include<memory>
using namespace std;

void mem1()
{
	while (1)
	{
		Sleep(3000);
		auto_ptr<double> ap(new double[1024 * 1024 * 10]);
		Sleep(3000);
	}
}
void mem2()
{
	while (1)
	{
		Sleep(3000);
		unique_ptr<double> up(new double[1024 * 1024 * 10]);
		Sleep(3000);
	}
}
void main()
{
	mem1();


	cin.get();
}