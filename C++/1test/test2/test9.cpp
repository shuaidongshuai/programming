#include <iostream>
#include <stack>
#include <set>

using namespace std;

int test9()
{
	set<int> s;
	int zero = 2;
	char ch;
	int sum = 0;
	while (zero > 0)
	{
		ch = getchar();
		if (sum == 0 && ch == '0')
		{
			zero--;
		}
		else if (ch >= '0' && ch <= '9')
		{
			sum = sum * 10 + ch - '0';
		}
		else if (sum && ch == ' ')
		{
			s.insert(sum);
			sum = 0;
		}
	}
	set<int>::iterator it = s.begin();
	for (; it != s.end(); ++it)
	{
		cout << *it << " ";
	}
	
	return 0;
}
/*
“@cipher&” 表示字符串cipher是使用方案1加密过的
“# cipher^” 表示字符串cipher是使用方案2加密过的
“$cipher%” 表示字符串cipher是使用方案3加密过的
“#c@hip&er^” 是组合的加密方式 表示 “hip”被方案1加密过， 加密前的字串和 ”c”与 “er”拼接后的字串是被方案2加密后的
*/
int test10()
{
	stack<char> s;
	char ch;
	while (cin >> ch)
	{
		if (ch == '@' || ch == '#' || ch == '$')
			s.push(ch);
		else if (ch == '&')
		{
			if (s.top() == '@')
				s.pop();
			else
			{
				cout << "false";
				return 0;
			}
		}
		else if (ch == '^')
		{
			if (s.top() == '#')
				s.pop();
			else
			{
				cout << "false";
				return 0;
			}
		}
		else if (ch == '%')
		{
			if (s.top() == '$')
				s.pop();
			else
			{
				cout << "false";
				return 0;
			}
		}
	}
	cout << "true";

	return 0;
}