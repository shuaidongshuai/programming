#include<stdio.h>
#include<stdlib.h>
typedef struct list
{
	int a;
	struct list *next;
	struct list *prev;
}str;
str * creat()
{
	str *p;
	p=(str *)malloc(sizeof(str)); 
	printf("请输入数据\n");
	scanf("%d",&p->a);
	return p; 
}
// 链表的初始化(自己指向自己)这个头结点是空的   但必须有
void INIT_LIST_HEAD(str *head)
{
	head->next=head;
	head->prev=head;
}
void __list_add(str *fresh,str *prev,str *next)
{
	next->prev = fresh;
	fresh->next = next;
	fresh->prev = prev;
	prev->next = fresh;
}
void list_add(str *head,str *fresh)
{
	__list_add(fresh,head,head->next);//插向头部 
}
void list_add_tail(str *head,str *fresh)//插向尾部 
{
	__list_add(fresh,head->prev,head);
}

void __list_del(str *prev,str *next)
{
	prev->next=next;
	next->prev=prev;
}
void list_del(str *p)
{
	__list_del(p->prev,p->next);
}
void del(str* head)
{
	str *p;
	p=head->next;
	int i;
	printf("请问要删除那个节点\n");
	scanf("%d",&i);
	while(--i)
	p=p->next;
	list_del(p);
}
void list_for_each(str *head)
{
	str *pos;
	printf("正向遍历："); 
	for (pos = (head)->next;pos != (head);pos = pos->next)
	printf("%-3d",pos->a);
	printf("\n"); 
}
void list_for_each_prev(str *head)
{
	str *pos; 
	printf("反向遍历：");
	for (pos = (head)->prev; pos != (head);  pos = pos->prev)
	printf("%-3d",pos->a);
	printf("\n"); 
}
int main()
{
	str *head;
	head=(str *)malloc(sizeof(str));
	INIT_LIST_HEAD(head);
	while(1)
	{
		int m;
		printf("1.向前添加数据\t2.向后添加数据\t3.删除节点\t7.正向遍历\t8.反向遍历\t9.清空链表\n");
		scanf("%d",&m);
		if(1==m)
		{
			str *fresh1;
			fresh1 = creat();
			list_add(head,fresh1);
		 }
		 if(2==m)
		 {
		 	str *fresh2;
		 	fresh2 = creat();
			list_add_tail(head,fresh2);
		 }
		 if(3==m)
		 {
		 	del(head);
		 }
		 if(7==m)
		 {
			list_for_each(head);
		 }
		 if(8==m)
		 {
			list_for_each_prev(head);
		 }
		 if(9==m)
		 {
			INIT_LIST_HEAD(head);
		 }
	}
 } 
