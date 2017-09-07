#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	char* p = "C:\\Users\\37916\\Desktop\\dong.txt";
	char ch;
	
	ofstream fout(p,ios::app);
	fout<<"³ÂÃ÷¶«"<<endl;
	
	ifstream fin(p,ios::in);
	while(fin.get(ch))
	{
		cout<<ch;
	}
}
