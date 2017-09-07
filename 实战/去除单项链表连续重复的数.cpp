#include<stdio.h>
#include<stdlib.h> 
typedef struct Node
{
	int a;
	struct  Node *next;
}NODE;
NODE *b()
{
	NODE *head,*t,*p;
	head=(NODE *)malloc(sizeof(NODE));
	scanf("%d",&head->a );
	t=head;
	while(1)
	{
		p=(NODE *)malloc(sizeof(NODE));
		scanf("%d",&p->a );
		if(p->a==0) break;
		t->next=p;
		p->next =NULL;
		t=p;
	}
	return head;
}
NODE *compress(NODE *head)
{
	NODE *q,*t;
	q=head;
	t=q->next ;
	while(q->next!=NULL)
	{
		if(q->a==t->a)
		{
		q->next=t->next ;
		t=q->next;
	}
	else
	{
		q=t;
		t=q->next ;
	}
}
	return head;
}
int main()
{
	printf("请输入链表的值：\n");
	NODE *head,*head1;
	head=b();
	head1=compress(head);
		printf("处理后的链表：\n");
	while(head1!=NULL)
	{
		printf("%d",head1->a);
		head1=head1->next ;
	}
 } 
