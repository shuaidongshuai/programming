#include<stdio.h>
#include<time.h>
void main()
{
time_t t;
struct tm *p;
time(&t);
p=gmtime(&t);
printf("Year :%d\n",1900+p->tm_year);
printf("Month :%d\n",1+p->tm_mon);
printf("Day :%d\n",p->tm_mday);
printf("Hour :%d\n",8+p->tm_hour);
printf("Minute :%d\n",p->tm_min);
printf("Weekday :%d\n",p->tm_wday);
printf("Days :%d\n",p->tm_yday);//the first day of the year
}
