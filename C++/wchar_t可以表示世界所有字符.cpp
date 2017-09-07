#include<iostream>
using namespace std;
int main()
{
	wchar_t w1='a',w2='³ÂÃ÷¶«';
	cout<<w1<<"\t"<<w2<<endl;
	cout<<sizeof(w1)<<"\t"<<sizeof(w2)<<endl;	
	cout<<sizeof(char)<<"\t"<<sizeof(wchar_t)<<endl;
}
