#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	while(1)
	{
		char s[32];
		cin>>s;
		
		int n = strlen(s) - 1;
		int m = 1;
		int sum = 0;
		while(n>=0)
		{
			sum += (s[n] - '0')*m;
			m*=2;
			n--;
		}
		cout<<"sum = "<<sum<<endl;
	}
}
