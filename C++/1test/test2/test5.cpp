#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
using namespace std;

extern int a;//声明
int b;//声明，并定义
extern int c = 20;//定义

void test5()
{
	//extern int d = 20;	//不能对带有块范围的外部变量进行初始化
}

char findMax(string s,int &index)
{
	char max = 0;
	int len = s.length();
	for (int i = 0; i < len; ++i)
	{
		if (max < s[i])
		{
			max = s[i];
			index = i;
		}
	}
	return max;
}
void test6()
{
	vector<string> v;
	string input;
	char cur, pre, next;
	int arr[1000][2];
	int n = 1;//第几个串
	int maxstr[2];//在那个串的哪个位置
	char max = 0;//最大的那个数
	int index = 0;//位置
	while (cin >> input && input[0] != '\n')
	{
		if (max < findMax(input,index))
		{
			maxstr[0] = n;
			maxstr[1] = index;
			max = findMax(input, index);
		}
		++n;
		v.push_back(input);
	}
}