#include<stdio.h>
#include<string.h>
int main()
{
char str1[40],str2[40];
int n;
gets (str1);
gets (str2);
n=strlen(str1)+strlen(str2);
printf("%d",n);
}
