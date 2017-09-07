#include <stdio.h>
#define r 16	//好像必须用define  定义的 元素 
#if r==16
void p(int a)
{
    printf("%x",a);
}
#else
void p(int a)
{
    printf("%d",a);
}
#endif
int main()
{
    p(32);
}
