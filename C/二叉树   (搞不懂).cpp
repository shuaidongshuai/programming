#include<stdio.h>
#include<stdlib.h>
typedef struct node
{
	struct node *lchild;
	char data;
	 struct node *rchild;
 } bitnode,*bitree;
 bitree greattree()
 {
 	char a;
	scanf("%c",&a);
	printf("dong\n");
	bitree n;
	if(a=='0') return NULL;
	else
	{
		n=(bitree)malloc(sizeof(bitnode));
		n->data=a;
		n->lchild=greattree();
		n->rchild=greattree();
	}
	return n;
 }
 void print(bitree bt)
 {
 	if(bt!=NULL)
 	{
 		print(bt->lchild);
 		printf("%c",bt->data);
 		print(bt->rchild);
 }
}
 int main()
 {
 	bitree root;
 	root=greattree();
 	print(root);
 }
 
