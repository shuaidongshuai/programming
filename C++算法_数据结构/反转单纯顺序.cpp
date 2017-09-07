#include <iostream>
using namespace std;
/*
"I am a student"   ----->      "student a am I"
*/ 

void Reverse(char *pBegin,char *pEnd)
{
	if(!pBegin || !pEnd)
		return;
	char temp;
	while(pBegin < pEnd)
	{
		temp = *pBegin;
		*pBegin = *pEnd;
		*pEnd = temp;
		pBegin++;
		pEnd--;
	}
}

void ReverseSentence(char *pData)
{
	if(!pData)
		return;
	char *pBegin,*pEnd;
	pEnd = pBegin = pData;
	while(*pEnd)
		++pEnd;
	--pEnd;
	//反转整个字符串
	Reverse(pBegin,pEnd);
	//反转局部字符
	pEnd = pBegin;
	while(*pEnd)
	{
		while(*pEnd && *pEnd != ' ')
			++pEnd;
		Reverse(pBegin,pEnd - 1);
		pBegin = ++pEnd;
	}
}

int main()
{
	char *s = new char[1024];
	cin.get(s,1024);
	ReverseSentence(s);
	cout<<s<<endl;
} 
