#include<stdio.h>
#include<stdlib.h>
typedef struct a
{
	int key;
	struct a *next;
}lnode,*link;
void j(link p,int m,int x)
{
	int i;
	link q;
	if(x==0) return;
	q=p;
	m%=x;
	if(m==0) m=x;
	for(i=1;i<=m;i++)
	{
		p=q;
		q=p->next;
	}
	p->next=q->next;
	i=q->key;
	printf("%d",i);
	free(q);
	j(p,i,x-1);
}
int main()
{
	int i,m,b[]={4,7,5,9,3,2,6,1,8};
	link head,t,q;
	head=(link)malloc(sizeof(lnode));
	if(!head) return 0;
	head->key=b[0];
	t=head;
	for(i=1;i<9;i++)
	{
		q=(link)malloc(sizeof(lnode));
		q->key=b[i];
		t->next=q;
		t=q;
	}
	t->next=head;
	printf("请输入一个数1~9:  ");
	scanf("%d",&m);
	printf("the output :\n");
	j(t,m,9);
	return 0;
}
