#include<stdio.h>
union k
{
	int a;
	int b;
 } ;
 union k s[4];
 union k *p;
 int main()
 {
 	int n=1,i;
 	for(i=0;i<4;i++)
 	{
 		s[i].a=n;
 		s[i].b=s[i].a+1;
 		n=n+2;
 		printf("%d   %d\n",s[i].a,s[i].b);
	 }
	 p=&s[0];
	 printf("%d\n",p->b);
	 printf("%d",++p->b);
 }
