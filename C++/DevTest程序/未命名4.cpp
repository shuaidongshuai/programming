#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	char *s1 = new char[8];
	char *s2 = new char[8];
	cin >> s1 >> s2;
	char *mulNum = new char[16];
	memset(mulNum, 0, 16);
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	for (int i = len1 - 1; i >= 0; i--)
	{
		for (int j = len2 - 1; j >= 0; j--)
		{
			mulNum[i + j + 1] += (s1[i] - '0') * (s2[j] - '0');
			if (mulNum[i + j + 1] > 9)
			{
				mulNum[i + j] += mulNum[i + j + 1] / 10;
				mulNum[i + j + 1] %= 10;
			}
		}
	}
	//没想到这次想到了这个问题，以前总是得不了满分，原因就在这啊
	if(0 == mulNum[1] && 0 == mulNum[0])	//说明整体为0 
		cout<<"0"<<endl;
	else//除了乘积为0的情况， mulNum[1] 和 mulNum[0] 不可能同时为0 （注意是两个正整数相乘） 
	{
		if (mulNum[0] != 0)
			cout << int(mulNum[0]);
		for (int i = 1; i < len1 + len2; i++)
			cout << int(mulNum[i]);
	} 
	return 0;
}

