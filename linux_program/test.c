#include <stdio.h>

long long func(int n)
{
    int i = 0;

    if (n > 20) {
        printf("n too large!\n");
        return -1;
    }
    if (n == 0) 
        return 1;
    else {
        i = n * func(n-1);
        return i;
    }
}

int main(void)
{
    long long ret;
    ret = func(10);
    printf("ret = %lld\n",ret);
    return 0;
}
