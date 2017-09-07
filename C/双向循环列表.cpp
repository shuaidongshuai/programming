#include<stdio.h>
#include<stdlib.h>
typedef struct list
{
	int a;
	struct list *next;
	struct list *prior;
}str;
int n;
str * creat(str *head)
{
	str *p,*pt;
	printf("要输入几个数据？\t");
	scanf("%d",&n);
	int m=n;
	printf("\n请输入\n"); 
	scanf("%d",&head->a);
	p=pt=head;
	while(m>1)
	{
		m--;
		p=(str *)malloc(sizeof(str));
		scanf("%d",&p->a);
		p->prior=pt;
		pt->next=p;
		pt=p;
	}
	head->prior=p;
	p->next=head;
	return head;
 } 
//遍历 
void gothrough(str *head) 
{
	str *p;
	p=head;
	printf("正向遍历\n");
	int m=n;
	while(m)
	{
		m--;
		printf("%-3d",p->a);
		p=p->next;
	}
	printf("\n反向遍历\n");
	m=n;
	while(m)
	{
		m--;
		p=p->prior;
		printf("%-3d",p->a);
	}
 }
//删除节点，不是删除数据 
void deletelist(str *head)
{
	printf("你要删除哪个节点?\t");
	int node;
	scanf("%d",&node); 
	
	str *front,*behind;
	front=behind=head;
	behind=behind->next;
	int m=n;
	if(node>2)
	while(node>2)
	{
		behind=behind->next;
		front=front->next;
		node--;
	}
	if(1==node)
	{
		head->a=behind->a;// 本来开始不是这样的，突然发现好像头结点不能删除，不然遍历会出问题 。所以换了一个方法 假删除头结点 
	}
	behind=behind->next;
	
	front->next=behind;
	behind->prior=front;
	head=front;
	n--;	
}
//插入节点，准确的说我只插入到了尾部，懒得很，今天还有很多事要做 插入中间其实也不难 
void insert(str *head)
{
	int a,node=n;
	str *p,*q,*str1;
	str1=(str *)malloc(sizeof(str));
	printf("\n你要插入的数\n");
	scanf("%d",&str1->a);
	
	p=head;
	while(node>1)
	{
		p=p->next;
		node--;
	}
	q=p->next;
	p->next=str1;
	str1->prior=p;
	q->prior=str1;
	str1->next=q;
	n++;
 } 
int main()
{
	str *head;
	int m;
	head=(str *)malloc(sizeof(str));// 重点**为他分配空间是必须的（1.其他函数没有对她进行分配空间  2.就算其他空间分配了空间也只能在那个函数中有效，我们要的是全局有效） 
	head=creat(head);
	gothrough(head);
	while(1)
	{
		printf("\n1.添加数据\t2.删除数据\t3.正反遍历\n");
		scanf("%d",&m);
		if(1==m)
		{
			insert(head);
		 } 
		 if(2==m)
		 {
			deletelist(head);
		 }
		 if(3==m)
		 {
		 	gothrough(head);
		 }
	}
 } 
