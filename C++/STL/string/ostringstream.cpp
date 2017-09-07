#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

int test9()
{
	ifstream ifile("C:\\Users\\37916\\Desktop\\1.txt");
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	cout << buf.str() << endl;
	return 0;
}