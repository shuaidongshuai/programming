#include<stdio.h>
void convert(int n,int base,int offset)
{
	char t[16] = {'0','1','2','3',
				  '4','5','6','7','8',
				  '9','A','B','C','D',
				  'E','F'};
	char arr[32];
	int i=0;
	
	//为什么要加上 &&i<32/offset 呢？  答：控制输出多少位， 如果是正数 n 右移最高位补 0（可以退出循环）\
															如果是负数右移最高位补 1  （不加控制输出多少位，，将会无限循环）  
	while(n!=0&&i<32/offset)
	{
		int temp = n&base; 
		arr[i++] = t[temp];
		n>>=offset;
	}
	while(--i>=0)//存入arr数组中的是  反向存储的 
	printf("%c",arr[i]);	
 } 
 
void toHex(int n)
 {
 	printf("toHex:");
 	convert(n,15,4);
 }
 
void to8(int n)
 {
 	printf("to8:");
 	convert(n,7,3);
 }
 
void toBin(int n)
 {
 	printf("toBin:");
 	convert(n,1,1);
 }
 
int main()
{ 
	int n;
	while(1)
	{
		scanf("%d",&n);
		toHex(n);
		printf("\n");
		to8(n);
		printf("\n");
		toBin(n);
		printf("\n");
	}
} 
  		

