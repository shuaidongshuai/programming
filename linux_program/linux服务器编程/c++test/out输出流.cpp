#include <iostream>
#include <fstream>
using namespace std;

void test()
{
	static const char *str = "nice to meet you";
	ofstream outfile("./outfile");//文件不存在也会自动创建
	if ( ! outfile ) 
		cout << "error: unable to open output file!\n" << endl;
	else
		outfile<<str<<endl;
}
void test2()
{
	static const char *str = "nice to meet you";
	ofstream outfile("./outfile",ios::app);//追加
	if ( ! outfile ) 
		cout << "error: unable to open output file!\n" << endl;
	else
		outfile<<str<<endl;
}
int main()
{
	//test();
	test2();
	
	return 0;
}
