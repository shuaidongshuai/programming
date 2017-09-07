#include<iostream>
#include <stack>
#include <string>
using namespace std;

int priority(char c)
{
	switch (c)
	{
	case '+':return 1;
	case '-':return 1;
	case '*':return 2;
	case '/':return 2;
	case '(':return 5;
	case ')':return 0;
	default: return -1;
	}
}
void error()
{
	cout << "你的表达式有问题,请仔细检查" << endl;
}
int cout_num(int a, int b, char c)
{
	switch (c)
	{
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a * b;
	case '/':return a / b;
	}
	error();
	return 0;
}
//对栈进行pop计算
int count_stack(stack<int> &data, stack<char> &symbol,char c = '#')
{
	char top = symbol.top();
	int sum;
	while (top != '#' && top != '(' && priority(top) >= priority(c))//不允许栈中有优先级小或一样的在最上面
	{
		int b = data.top();
		data.pop();
		int a = data.top();
		data.pop();
		sum = cout_num(a, b, top);
		data.push(sum);
		symbol.pop();
		top = symbol.top();
		if (top == '(')
			symbol.pop();
	}
	return data.top();
}
int count_expression(string str)
{
	stack<char> symbol;
	stack<int> data;
	int index = 0, sum = 0;
	symbol.push('#');//标志位，当top到#的时候说明没有符号了
	data.push(0);
	while (!symbol.empty())
	{
		if (str[index] == 0)
		{
			sum = count_stack(data, symbol, str[index]);
			break;
		}
		else if (str[index] >= '0' && str[index] <= '9')
		{
			int num = str[index++] - '0';
			while (str[index] >= '0' && str[index] <= '9')
				num = num * 10 + str[index++] - '0';
			data.push(num);
			continue;
		}
		else
		{
			if (!symbol.empty())//如果栈不为空
				count_stack(data, symbol,str[index]);
			if (str[index] != ')')
				symbol.push(str[index]);
		}
		++index;
	}
	return sum;
}

int main()
{
	//string str = "1+(((23+34)*5)*2)-6";
	string str = "1+2*3";
	//string str;
	//cin >> str;
	cout << count_expression(str) << endl;
	system("pause");
	return 0;
}
/*
代码还有点问题，没有完全满分
*/