#include "common.h"

string getMaxStr(string s1, char* str2,int index,int len)
{
	string sdiv = s1.substr(index, len);
	if (len > strlen(str2) || len == strlen(str2) && strcmp(sdiv.c_str(), str2) > 0)//长度大于str2 || //数值大于str2
		return sdiv;

	getMaxStr(s1, str2, ++len, index);
}
string div(char* str1, char* str2)
{
	string res = "";
	string s1 = str1;
	int n1 = strlen(str1);
	int n2 = strlen(str2);
	if (n2 > n1)
		return "0";
	if (n2 == n1 && strcmp(str1, str2) < 0)
		return "0";

	int j;
	char temp;
	string sdiv = getMaxStr(s1, str2, 0, n2);
	string div;
	for (int i = 0; n2 <= n1; i++)
	{
		for (j = 1; j < 9; j++)
		{
			temp = j + '0';
			div = mul((char *)sdiv.c_str(), &temp);

		}
		res += temp;

		//sdiv = getMaxStr(s1,str2,)
	}


	return nullptr;
}