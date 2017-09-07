#include<stdio.h>
int main()
{
    int t,i,a[10],*p,*q;
    for(i=0; i<10; i++)
        a[i]=i+1;
    for(i=0; i<5; i++)
    {
        p=a+i;
        q=a+9-i;
        t=*p;
        *p=*q;
        *q=t;
    }
    for(i=0; i<10; i++)
        printf("%d  ",a[i]);
}
