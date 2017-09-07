#include<stdio.h>
#include<stdlib.h>
int m,n;
struct node
{
	int i;
	struct node *next;
 };
 struct node *creat(struct node *head);
 void print(struct node *head);
 void add(struct node *head,int p,int q);
 void del(struct node *head,int P);
int main()
{
	int ch,P,Q;
	char a[10];
	struct node *head;
	head=NULL;
	scanf("%d%d",&n,&ch);
	m=n;
	head=creat(head);
	while(ch!=0)
	{
		scanf("%s",a);
		if(a[0]=='A')
		{
		scanf("%d%d",&P,&Q);
		add(head,P,Q);
		m++;
		}
		if(a[0]=='D')
		{
		scanf("%d",&P);
		del(head,P);
		m--;
		}		
	ch--;
	}
	printf("%d\n",m);
	print(head);
	return 0;
}
struct node *creat(struct node *head)
{
	struct node *t,*p;
	t=(struct node *)malloc(sizeof(struct node));
	scanf("%d",&t->i);
	t->next=NULL;
	head=t;
	while(n>1)
	{
		p=(struct node *)malloc(sizeof(struct node));
		scanf("%d",&p->i);
		t->next=p;		
		t=p;
		n--;
	}
	t->next=NULL;
	return head; 
}
void print(struct node *head)
{
	int a=0;
	while(head!=NULL)
	{
		printf("%d ",head->i);
		head=head->next;
	}	
}
void add(struct node *head,int P,int Q)
{
	struct node *t,*q,*p;
	t=p=head;
	if(t->i!=P)
	{
		while(1)
	{
		p=t->next;
		if(p->i==P)
		break;
		t=t->next ;
	}
	q=(struct node *)malloc(sizeof(struct node));
	q->i=Q;
	t->next=q;
	q->next=p;	
	}
	else
	{
		p=t->next ;
		q=(struct node *)malloc(sizeof(struct node));
		q->i=t->i;
		t->i=Q;
		t->next=q;
		q->next=p;
	}
}
void del(struct node *head,int P)
{
	struct node *t,*q;
	t=head;
	if(t->i!=P)
	{
	while(1)
	{
		q=t->next;
		if(q->i==P)
		break;
		t=t->next ;
	}
	t->next=q->next ;		
	}
	else
	{
		t=head->next ;
		head->i=t->i;
		head->next =t->next ;
	}
}
