#include<stdio.h>
#include<string.h>
char str1[100001],str2[100001];
void add(char a[])									// 向后添加0 1 
{
	strcat(str2,a);
}
int main()
{
	str2[0]='\0';									// 没哟这一步  第一次就不能执行add 中的 strcat 
	scanf("%s",str1);
	int i,a=strlen(str1);
	//十六进制转换为2进制 
	//首先判断这个2进制数  是否能够被3整除
	if(a%3==1)											// str1  和 str2的长度  是4倍关系  用  str1   的长度是一样的效果 
	add("00");
	else if(a%3==2)
	add("0");
	for(i=0;i<a;i++)
	{
		switch(str1[i])
		{
			case '0':add("0000");break;
			case '1':add("0001");break;
			case '2':add("0010");break;
			case '3':add("0011");break;
			case '4':add("0100");break;
			case '5':add("0101");break;
			case '6':add("0110");break;
			case '7':add("o111");break;
			case '8':add("1000");break;
			case '9':add("1001");break;
			case 'A':add("1010");break;
			case 'B':add("1011");break;
			case 'C':add("1100");break;
			case 'D':add("1101");break;
			case 'E':add("1110");break;
			case 'F':add("1111");break;
			default:break;
		}
	}
	//现在进行2进制转化为8进制
	int b=strlen(str2);
	for(i=0;i<b;i+=3)									// i<b  这个的仔细思考   很容易出错 
	{
		str1[i]=(str2[i+2]-'0'+(str2[i+1]-'0')*2+(str2[i]-'0')*4)+'0';			// 这一步也很容易出错 ，  仔细思考 
		if(i==0&&str1[i]=='0')							//  算出来有可能第一位（最高位）为0  因为可能添加了两个00  加上原来的几个0  会造成最高位为0 
		continue;										//  但是不可能 前两位都为 0     因为这个2进制数前面最多5个0    2进制3位 当8进制1位 
		printf("%c",str1[i]);
	}
	return 0;
}
