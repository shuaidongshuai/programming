#include<stdio.h>
#include<time.h>
int main()
{
time_t p;
time(&p);
printf("NOW:%ld\n",p);
return 0;
}

