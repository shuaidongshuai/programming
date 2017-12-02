#include <iostream>
#include <cstdlib> 
using namespace std;

/* 注意：1.不仅返回值，还要返回状态g_status
		 2.判断参数是否为空，参数的内容是否为空
		 3.判断正负号
		 4.在转化为整数的时候，判断每一位是否是0 - 9
		 5.判断有没有越界（正负越界） */ 

enum Status{value = 0,invalue};
int g_status = invalue;

int my_atoi(char *str)
{
	if(!str || !*str)
		return 0;
	while(*str == ' ')//atoi()会扫描,跳过前面的空格字符
		++str;
	long long sum = 0;
	bool fu = false;
	if(*str == '-')
	{
		fu = true;
		++str;
	}
	else if(*str == '+')
		++str;
	if(*str == 0)
		return 0;
	while(*str)
	{
		if(*str >= '0' && *str <= '9')
		{
			sum = sum * 10 + *str - '0';
			++str;
			if((fu && sum > 0x80000000) || (!fu && sum > 0x7fffffff))
				return 0;
		}
		else
			break;
	}
	if(fu)
		sum = 0 - sum;
	g_status = value;
	return int(sum);
}

void print(char *str){
	cout<<my_atoi(str)<<endl;
	cout<<atoi(str)<<endl;
	cout<<"--------------------"<<endl;	
}
int main()
{
	char *str1 = "+123";
	print(str1);
	
	str1 = "   -111   22 fads";
	print(str1);
	
	str1 = ""; 
	print(str1);
	
	str1 = NULL;
	print(str1);
}

