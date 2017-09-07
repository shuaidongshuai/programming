//十进制转化为十六进制  8进制 
#include<stdio.h>
int main()
{
	int i;
	char str[40];
		scanf("%s", str);
		sscanf(str,"%d", &i);
		printf("十进制：%d\n十六进制：0x%x\n八进制：0%o", i, i, i);
}
