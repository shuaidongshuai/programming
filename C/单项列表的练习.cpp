#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct student
{
int num;
char name[20];
float score;
struct student *point;
};
int main()
{
struct student *head,*end,*next,*p;
int i,snum;
char sname[20];
float sscore;
head=(struct student *)malloc(sizeof(struct student));
if(head==NULL)
{
printf("failure");
}
else
{
scanf("%d%f",&snum,&sscore);
scanf("%s",sname);
head->num=snum;
strcpy(head->name,sname);
head->score=sscore;
end=head;
for(i=1;i<4;i++)
{
next=(struct student *)malloc(sizeof(struct student));
scanf("%d%f",&snum,&sscore);
scanf("%s",sname);
next->num=snum;
strcpy(next->name,sname);
next->score=sscore;
next->point=NULL;
end->point=next;
end=next;
}
}
p=head;
printf("num     name     score\n");
while(i!=0)
{
	i--;
printf("%d      %s       %f\n",p->num,p->name,p->score);
p=p->point;
}
}
