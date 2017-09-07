#include<iostream>
using namespace std;
int main()
{
	char data[80];
	cin.read(data,80);
	data[cin.gcount ()]='\0';//按ctrl+z回车结束输入（必须独自在一行输入） 
	
	cout<<endl<<data<<endl;
	cout<<"---------------------"<<endl;
	cout.write(data,80);	//这种输出吧ctrl+z也输出了    所以最后面有乱码 
	cout<<endl;
	return 0;
}
