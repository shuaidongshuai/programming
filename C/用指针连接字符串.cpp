#include<stdio.h>
int mystrlen(char s[]) {
 int len = 0;
 while(s[len]) ++len;
 return len;
}
char *mystrcat(char *s1,char *s2) { // ָ�뷨
 int len = mystrlen(s1);
 char *p = s1 + len;
 while(*p++ = *s2++);
 return s1;
}
int main()
{
	char a[]="hello ";
	char b[]="world";
	printf("%s",mystrcat(a,b));
 } 
