#include<Windows.h>
#include<thread>
#include <iostream>
using namespace std;

void run1()
{
	static int 陈明东 = 1;
	cout << "I am run1------------   " << 陈明东++ << "   " << endl;
}

void run2()
{
	cout << "run2++++++++++++++++" << endl;
}

int main()
{
	for (int i = 0; i < 10; i++)
	{
		new thread(run1);
		new thread(run2);
		Sleep(100);
	}

	system("pause");
}