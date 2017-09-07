#include<stdio.h>
int main()
{
	int z,b,c,d,other;
	while((z=getchar())!='\n')
	{
		if((z>='a'&&z<='z')||(z>='A'&&'Z')) b++;
		else if(z==' ') c++;			/*结束符“回车”也算在了‘ ’里*/ 
		else if(z>='0'&&z<='9') d++;
		else other++;
	}
	printf("字母个数%d\t空格%d\t数字%d\t其他%d",b,c-1,d,other);
 } 
