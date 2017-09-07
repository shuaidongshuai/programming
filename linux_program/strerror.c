#include<stdio.h>
#include<string.h>
#include<errno.h>
void main()
{
int i;
for(i=1;i<=15;i++)
{
printf("Errno:%d ",i);
printf("Message:%s\n",strerror(i));
}
}

