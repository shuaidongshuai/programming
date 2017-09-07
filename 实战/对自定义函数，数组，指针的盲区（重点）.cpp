#include<stdio.h> 
void dong(char *a,char *b,char c[])			//目前认为不带返回值的自定义函数只能用指针huozhe用a[]数组 改变地址来达到目的，如果换成一个变量，对外面的函数没有影响 
{
	*a='&';
	*b='*';
	c[1]='0';
	c[2]='9';
 } 
 int main()
 {
 	int i;
 	char *c,*d,a[5],b[5],e[5];
 	gets(a);
 	gets(b);
 	gets(e);
 	c=a;
 	d=b;
 	for(c,d;c<=a+2;c++,d++)
 	dong(c,d,e);
 	for(i=0;i<4;i++)				//这样也可以吧字符输出 
 	printf("%c,%c\n",a[i],b[i]);
 	printf("%s,%s\n",a,b);			//这样可以吧全部字符输出来 ，，，不能换成指针，因为指针已经到末尾了
 	printf("%s\n",e);
}
