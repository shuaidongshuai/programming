#include<stdio.h>
int main()
{
	int i = 0x10203040;
	char *p = (char *)(&i);
	printf("内存地址 ：%x  %x\n",p,*p);
	printf("内存地址 ：%x  %x\n",p+1,*(p+1));
	printf("内存地址 ：%x  %x\n",p+2,*(p+2));
	printf("内存地址 ：%x  %x\n",p+3,*(p+3));	
}
/*
内存地址 ：4ac491ac  40
内存地址 ：4ac491ad  30
内存地址 ：4ac491ae  20
内存地址 ：4ac491af  10

*/
