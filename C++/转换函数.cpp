#include<iostream>
#include<string.h>
using namespace std;
class cmoney
{
	double amount;
public:
	cmoney(double a=0)
	{
		amount=a;
	}
	 operator char*();   //转换函数
};
cmoney::operator char*()
{
	char *ba[15]={"分","角","元","十","百","千","万","十","百","千","亿","十","百","千","万"};
	char *da[10]={"零","壹","貳","叁","肆","伍","六","柒","捌","玖"};
	static char str[80];
	double temp,base=1;
	int n=0;
	temp=amount*100;
	cout<<temp<<endl;
	strcpy(str,"金额为:");
	if(temp<1)
		strcpy(str,"要大于一角钱");
	else
	{
		while(temp>=10)
		{
			base*=10;
			temp/=10;
			n++;
		}
		if(n>=15)
			strcpy(str,"钱太多了");
		else
		{
			temp=amount*100;
			for(n;n>=0;n--)
			{
				int d=temp/base;
				temp=temp-base*d;
				base=base/10;
				strcat(str,da[d]);
				strcat(str,ba[n]);
			}
		}
	}
		return str;
}
int main()
{
	cmoney money(1234123456789.123);
	cout<<(char*)money<<endl;			//调用转换函数
	return 0;
}
