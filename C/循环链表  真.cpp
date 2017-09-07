#include <stdio.h>
#include<stdlib.h>
typedef struct list
{
int num;
struct list *next;
}List;
int n=0;
List *creat()
{
List *head,*p1,*p2;
int i;
head=(List *)malloc(sizeof(List));
p1=p2=head;
head->num=0; 
printf("ÊäÈëÊı¾İ£º\n");
for(i=0;i<20;i++)
{
p1=(List *)malloc(sizeof(List));
scanf("%d",&p1->num);
p2->next=p1;
p2=p1;
}
p1->next=head;
return(head);
}
void print(List *head)
{
	int i;
for(i=0;i<20;i++)
{
printf("%d ",head->num);
head=head->next;
}
printf("\n");
}
int  main()
{
List *head;
head=creat();
print(head);
}
