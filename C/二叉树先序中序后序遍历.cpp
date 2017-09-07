#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct NODE{
	int val;
	struct NODE *left;
	struct NODE *right;
	NODE(int val):val(val),left(NULL),right(NULL){}		//初始化支持 TreeNode（int x）这种方式，即 把x赋给val，left和right赋值NULL 
}Node,*Tree;
//建立的是排序 二叉树  所以不允许出现相同的数 
void create(Tree &p,int val)//这个没用双指针，但是也相当于双指针，这个是  指针取地址   指针取地址也就相当于二级指针(错了，，是引用)
{
	if(p==NULL)//不用向双指针那么复杂，，可以直接操作 一级指针 p   如果是双指针  就要用 (*p)->  比较麻烦   (这个 &p 好像是c++中的引用)
	p = new Node(val);
	
	else
	{
		if(val < p->val) //当前值 小于 父 的值
		create(p->left,val);
		
		if(val > p->val)//当前值  大于 父 
		create(p->right,val);
	}
 } 
 /* 下面这个用来 双指针 
 void create(Tree *p,int val)
{
	if(*p==NULL)
	*p = new Node(val);
	
	else
	{
		if(val < (*p)->val) //当前值 小于 父 的值
		create(&(*p)->left,val);
		
		else if(val > (*p)->val)
		create(&(*p)->right,val);
		
		else
		printf("有重复的数了%d\n",val);
	}
 } 
 */
 
void visit(Tree t)
{
	if(t->val != NULL)
	printf("%-5d",t->val);
}
void preOrder(Tree t)
{
 	if(p != NULL)
 	{
 //		visit(p);  	//不用这个  不知道为什么  0 会被认为是 NULL 	解惑：NULL 的宏定义就是 0	
 		printf("%-5d",p->val);
		preOrder(p->left);
		preOrder(p->right);	
	 }
}
void inOrder(Tree t)
 {
 	if(p != NULL)
 	{ 		
		preOrder(p->left);
		printf("%-5d",p->val);
		preOrder(p->right);	
	 }
}
 void postOrder(Tree t)
{
 	if(p != NULL)
 	{ 		
		preOrder(p->left);
		preOrder(p->right);	
		printf("%-5d",p->val);	
	 }
 }
 int main()
 {
 	int a[20];
 	Tree root = NULL;
 	for(int i=0;i<10;i++){
 	 	a[i] = rand()%100;
		printf("%-5d",a[i]);	
	 }
	for(int i=0;i<10;i++)
 	create(root,a[i]);

	puts("\n\n先序排序法");
	preOrder(root);
	
	puts("\n中序排序法");
	inOrder(root);
	
	puts("\n后序排序法");
	postOrder(root); 
 	return 0;
 }
