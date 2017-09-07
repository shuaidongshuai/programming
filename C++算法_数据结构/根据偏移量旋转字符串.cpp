#include <iostream>
#include <cstring>
using namespace std;

//根据偏移量旋转字符串      对于abc  偏移1  ->  cab     2 ->  bca 

void rotateString(char *str,int offset)
{
	if(!str || offset < 0)
		return;
	int len = strlen(str);
	if(offset > len)
		return;
	char *tempStr = new char[offset];
	for(int i = 0; i < offset; i++)
		tempStr[i] = str[len - i - 1];
	for(int i = len - offset - 1; i >= 0; i--)
		str[i + offset] = str[i];
	for(int i = 0;i<offset;i++)
		str[i] = tempStr[offset - i - 1];
}

int main()
{
	char *str = new char[10];
	int offset;
	while(1)
	{
		cin>>str>>offset;
		rotateString(str,offset);
		cout<<str<<endl;
	}
}
