#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	char a = 0x79;//127
	unsigned int b = a;
	cout << hex << (int)a << "  " << b << endl;

	char a1 = 0x80;//128
	unsigned int b1 = a1;
	cout << hex << (int)a1 << "  " << b1 << endl;

	system("pause");
	return 0;
}


