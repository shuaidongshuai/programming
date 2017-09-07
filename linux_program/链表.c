#include<stdio.h>
#include<stdlib.h>
#define SIZE sizeof(struct student)
typedef struct student
{
char name[20];
int score;
struct student *next;
}stu;
stu *main1()
{
stu *head,*end,*p;
p=(stu *)malloc(SIZE);
scanf("%s",p->name);
scanf("%d",&p->score);
head=end=p;
int i=2;
while(i>0)
{
p=(stu *)malloc(SIZE);
scanf("%s",p->name);
scanf("%d",&p->score); 
end->next=p;
end=p;
i--;
}
end->next=NULL;
return head;
}
void main()
{
stu *head;
head=main1();
while(head!=NULL)
{
printf("%s,%d\n",head->name,head->score);
head=head->next;
}
}















