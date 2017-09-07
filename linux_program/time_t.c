#include<stdio.h>
#include<time.h>
int main()
{
time_t t;
t=time((time_t*)NULL);
printf("NOW:%ld\n",t);
return 0;
}
