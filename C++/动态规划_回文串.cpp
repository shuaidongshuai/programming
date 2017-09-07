#include <string>
#include <cstring>
#include <iostream>
#include<algorithm>
using namespace std;
/*
提到回文串，自然要利用回文串的特点，想到将源字符串逆转后，“回文串”（不一定连续）相当于顺序没变
求原字符串和其反串的最大公共子序列（不是子串，因为可以不连续）的长度（使用动态规划很容易求得），
然后用原字符串的长度减去这个最大公共子串的长度就得到了最小编辑长度。
*/

int getMaxStr(string s1, string s2)
{
	int len1 = s1.size() + 1;
	int len2 = len1;
	int **max_len = new int*[len1];
	for (int i = 0; i < len1; i++)
	{
		max_len[i] = new int[len2];
		memset(max_len[i], 0, len2*sizeof(int));
	}

	for (int i = 1; i < len1; i++)
	{
		for (int j = 1; j < len2; j++)
		{
			if (s1[i - 1] == s2[j - 1])
				max_len[i][j] = max_len[i - 1][j - 1] + 1;
			else
				max_len[i][j] = max(max_len[i][j - 1], max_len[i - 1][j]);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i<len1; i++)
	{
		for (int j = 0; j<len2; j++)
		{
			cout << max_len[i][j] << " ";
		}
		cout << endl;
	}
	return max_len[len1 - 1][len2 - 1];
}

int main()
{
	string s1;
	while (cin >> s1)
	{
		string s2 = s1;
		reverse(s1.begin(), s1.end());
		cout << s1.size() - getMaxStr(s1, s2) << endl;
	}
	return 0;
}
