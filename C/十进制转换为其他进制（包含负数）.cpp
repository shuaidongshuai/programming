#include<stdio.h>
int toHex(int n)
{
	char t[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'} ;//16进制的表 
	char arr[32];
	int i=0;
	
	while(n!=0&&i<8)//整形 转化为 十六进制 有8位 （32/4 = 8） 
	{
		int temp = n&15; 
		arr[i++] = t[temp];//根据下表  直接查表（是一一对应的关系） 
		n>>=4;
	}
	printf("toHex:");
	while(--i>=0)
	printf("%c",arr[i]);
 } 
 int toBin(int n)
 {
 	char t[2] = {'0','1'};
 	char arr[32];
 	int i=0;
	
	while(n!=0&&i<32)//整形 转化为 二进制 有32位 
	{
		int temp = n&1; 	//取最低位 
		arr[i++] = t[temp];//根据下表  直接查表（是一一对应的关系） 
		n>>=1;
	}
	printf("toBin:");
	while(--i>=0)
	printf("%c",arr[i]);//根据下表  直接查表（是一一对应的关系） 	
} 
int main()
{
	int n;
	while(1)
	{
		scanf("%d",&n);
		toHex(n);
		printf("\n");
		toBin(n);
		printf("\n");
	}
} 
