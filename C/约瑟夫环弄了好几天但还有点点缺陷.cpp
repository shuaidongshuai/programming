#include<stdio.h>
#include<stdlib.h>
typedef struct o
{
	int key;
	struct o *next;
}link;
link *dong()
{
	int a[9]={4,7,5,9,3,2,6,1,8},i;
	link *head,*p1,*p2;
	head=(link *)malloc(sizeof(link));
	head->key =a[0];
	head->next =NULL;
	p1=head;
	for(i=0;i<8;i++)
	{
		p2=(link *)malloc(sizeof(link));
		p2->key=a[i+1];
		p1->next=p2;
		p1=p2;
	}
	p1->next =head;
	return(head);
}
void cmd(link *head,int x,int m)
{
	int i;
	link *q;
	if(m==0) return;
	x=x%m;
	q=head;
	if(x==0) x=m;
	for(i=1;i<=x;i++)
	{
		head=q;
		q=head->next ;
	}
	head->next=q->next ;
	i=q->key ;
	printf("%d  ",i);
	free(q);
	cmd(head,i,m-1);
}
int main()
{
	link *head;
	head=dong();
	cmd(head,3,9);
}
