#include<stdio.h>
#include<string.h>
int main()
{
	int a=11456,n,i;
	char s[10];
	sprintf(s,"%d",a);		//sprintf  可以吧整数分离成字符，，这样每位数都可以直接表示 
	i=strlen(s);
	for(n=0;n<i;n++) 
	printf("%5c",s[n]);
	printf("\n");
 } 
