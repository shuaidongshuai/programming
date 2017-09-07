#include <iostream>
#include <bitset>
using namespace std; 
/*
可能有多组测试数据，对于每组数据，
对于字符串中的每一个字符，输出按题目进行奇偶校验后的数，每个字符校验的结果占一行。
输入例子:
3
3a
输出例子:
10110011
10110011
01100001
*/
//核心思想是用与运算得出ASCII码的二进制形式和ASCII字符中1的个数

int main()
{
	char c;
	int i;
	bitset<8> bit; 
	while(cin>>c)
	{
		if(c == ' ' || c == '\n')
			continue;
		bit = c;
		if((bit.count() & 1) == 0)//如果是奇数 
			bit.set(7);
		cout<<bit<<endl;
	}
	return 0;
}

