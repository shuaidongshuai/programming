#include "common.h"
string sub(char* str1, char* str2)
{
	string res;//保存最终结果
	int n1 = strlen(str1);
	int n2 = strlen(str2);
	//我们要保证str1 大于 str2
	if (n1 <= n2)
	{
		int cmp = strcmp(str1, str2);
		if (cmp == 0)
			return "0";
		if (n1 < n2 || cmp < 0)//n1<n2换 n1 == n2 && cmp<0换
		{
			char* temp = str1;
			str1 = str2;
			str2 = temp;
			n1 += n2;
			n2 = n1 - n2;
			n1 -= n2;
			res = "-";
		}
	}
	char *str3 = new char[n1];
	for (int i = n1 - 1; i >= 0; i--)
	{
		if (--n2 >= 0)
			str1[i] = str1[i] - str2[n2] + '0';
		if (str1[i] < '0')
		{
			str1[i - 1] -= 1;
			str1[i] += 10;
		}
	}
	string res2 = str1;
	if (str1[0] == '0')
		res2.erase(0, 1);
	return res + res2;
}