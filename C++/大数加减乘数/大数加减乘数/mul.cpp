#include "common.h"
string mul(char* str1, char* str2)
{
	string res = "";
	int n1 = strlen(str1);
	int n2 = strlen(str2);
	char *str3 = new char[n1 + n2];
	//memset(str3, '0', n1 + n2);//这样初始化虽然简单，但是有一个bug  当9*9 + '0'时 char上存的是129 已经超过了128字节
	memset(str3, 0, n1 + n2);
	for (int i = n1 - 1; i >= 0; i--)
		for (int j = n2 - 1; j >= 0; j--)
		{
			str3[i + j] += (str1[i] - '0') * (str2[j] - '0');
			if (str3[i + j] > 9 && i + j > 0)
			{
				str3[i + j - 1] += str3[i + j] / 10;
				str3[i + j] = str3[i + j] % 10;
			}
		}
	if (str3[0] > 9)
	{
		res = str3[0] / 10 + '0';
		str3[0] = str3[0] % 10;
	}
	if (str3[1] == 0)
		str3 = "0";
	for (int i = n1 + n2 - 2; i >= 0; i--)
		str3[i] += '0';
	

	return res + str3;
}