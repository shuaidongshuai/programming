#include<iostream>
#include <stack>
#include <cstring>
using namespace std;

int priority(char c)
{
	switch (c)
	{
	case '+':return 1;
	case '-':return 1;
	case '*':return 2;
	case '/':return 2;
	case '^':return 3;
	case '%':return 3;
	case '('://加上这个，只为程序更加健壮，让我们捕捉到错误
	case ')':
	default: return 0;
	}
}

void error()
{
	cout << "你的表达式有问题,请仔细检查" << endl;
}

bool change(char s1[], char* &s2)
{
	stack<char> stack;
	char ch = s1[0];
	int i = 0;//记录s1现在的位置 
	int j = 0;//记录s2的位置 

	while (ch != '\0')
	{
		if (ch >= '0'&&ch <= '9' || ch == '.' || ch == ' ')
		{
			s2[j++] = ch;
			ch = s1[++i];
		}
		else if (ch == '(')
		{
			stack.push(ch);
			ch = s1[++i];
		}
		else if (ch == ')')
		{
			if (stack.empty())
			{
				error();
				return false;
			}
			while ((ch = stack.top()) != '(')
			{
				s2[j++] = ch;
				stack.pop();
			}
			if (ch != '(')
			{
				error();
				return false;
			}

			stack.pop();
			ch = s1[++i];
		}
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%')
		{
			if (!stack.empty())
			{
				char top = stack.top();
				//不允许栈中有优先级小的在优先级大的元素上面 
				//如果栈中的优先级比当前大，那么就输出栈中的元素  直到栈中所有元素都比它小 
				while (priority(top) >= priority(ch))//这个循环有必要，因为当前元素要入栈，里面优先级高的必须先出来
				{
					s2[j++] = top;
					stack.pop();
					if (stack.empty())
						break;
					top = stack.top();
				}
			}
			stack.push(ch);//栈中没有比它优先级更小的了   入栈 
			ch = s1[++i];
		}
		else
		{
			error();
			return false;
		}
	}
	while (!stack.empty())
	{
		ch = stack.top();
		s2[j++] = ch;
		stack.pop();
	}
	s2[j] = '\0';
	return true;
}

int main()
{
	char s1[] = "( 5 + 2 ) + 3 * 2 ^ 2 - ( 4 - 6 ) * 12 + 4 + 32 -1 + 42";//好奇怪啊字符串>=28之后return 不回来了
	cout << "len = " << strlen(s1) << endl;
	char* s2 = new char(strlen(s1) + 1);

	if (change(s1, s2))
	{
		cout << s2 << endl;
	}
	return 0;
}
