#include<stdio.h>
int main()
{
	int i = 0x10203040;
	char *p = (char *)&i;
	//char *p = (char *)pp;
	printf("内存地址 ：%x  %x\n",p,*p);
	printf("内存地址 ：%x  %x\n",p+1,*(p+1));
	printf("内存地址 ：%x  %x\n",p+2,*(p+2));
	printf("内存地址 ：%x  %x\n",p+3,*(p+3));
}
