#include<stdio.h>
int main()
{
	struct date
	{
		int year;
		int month;
		int day;
	};
	struct student
	{
		int num;
		char name[20];
		struct date birth;
	}stu[2]={{110,"王二",1996,02,22},{119,"张三",1996,01,04}};
	int i;
		printf("1^^^学号    姓名    出生日期\n");
	for(i=0;i<2;i++)
	{
	    printf("    %d      %s      %d-%d-%d\n",stu[i].num,stu[i].name,stu[i].birth.year,stu[i].birth.month,stu[i].birth.day);
	}
		printf("2^^^学号    姓名    出生日期\n");
	for(i=0;i<2;i++)
	{
	    printf("    %d      %s      %d-%d-%d\n",stu[i].num,stu[i].name,stu[i].birth.year,stu[i].birth.month,stu[i].birth.day);
	}
 } 
