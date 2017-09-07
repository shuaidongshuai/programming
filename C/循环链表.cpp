#include<stdio.h>
#include<stdlib.h>
typedef struct dong
{
	int d;
	struct dong *next;
}link;
int main()
{
	int a[5]={1,2,3,4,5},i,shuchu;
	link *p,*t,*head;
	head=(link *)malloc(sizeof(link));
	head->d=a[0];
	t=head;
	for(i=1;i<=4;i++)
	{
		p=(link *)malloc(sizeof(link));
		p->d=a[i];
		t->next=p;
		t=p;
	}
	t->next=head;
	for(i=0;i<20;i++)
	{ 
	shuchu=head->d;
	head=head->next ;
	printf("%d  ",shuchu);
}
}
