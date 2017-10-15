#include <iostream>
#include <cstdlib>
using namespace std;
typedef struct node
{
	char data;
	int ltag, rtag;
	struct node *lchild, *rchild;
}bitree;
bitree *Q[32], *pre = NULL;

//建树
bitree *create()
{
	bitree *s, *root;
	int front, rear;
	char x;

	front = 1; rear = 0;
	root = NULL;
	x = getchar();
	while (x != '$')
	{
		rear++;
		s = NULL;
		if (x != '@')
		{
			Q[rear] = (bitree*)malloc(sizeof(bitree));
			Q[rear]->data = x;
			Q[rear]->ltag = 0;
			Q[rear]->rtag = 0;
			Q[rear]->lchild = NULL;
			Q[rear]->rchild = NULL;
			if (rear == 1)
				root = Q[rear];
			else
			{
				if (rear % 2 == 0)
					Q[front]->lchild = Q[rear];
				else
					Q[front]->rchild = Q[rear];
				if (rear % 2 == 1)
					front++;
			}
		}
		else
		{
			Q[rear] = s;
			if (rear % 2 == 1)
				front++;
		}
		x = getchar();
	}
	getchar();
	return root;
}
//中序遍历
void Inorder(bitree *t)
{
	if (t)
	{
		Inorder(t->lchild);
		printf("%c", t->data);
		Inorder(t->rchild);
	}
}
//线索化 (中序线索化）   //把左节点为空的全部指向他的上一个节点，右节点为空的全部指向他的下一个节点
void Thread1_sys(bitree *t)
{
	bitree *p = t;
	if (p)
	{
		Thread1_sys(p->lchild);
		/*其实左孩子指向上一个节点，我感觉没啥用，完全不影响遍历*/
		if (p->lchild == NULL)		//左孩子为空的话，指向他的上一个节点
		{
			p->ltag = 1;//标志，以便我们遍历容易遍历
			p->lchild = pre;
		}
		if (pre->rchild == NULL)	//上一个节点右孩子为空，则指向现在这个节点
		{
			pre->rtag = 1;//标志，以便我们遍历容易遍历
			pre->rchild = p;
		}
		pre = p;
		Thread1_sys(p->rchild);
	}
}
void Thread(bitree *t)
{
	Thread1_sys(t);
	pre->rtag = 1;
}
void Thread2_sys(bitree *t, bitree *&pre2)
{
	bitree *p = t;
	if (p)
	{
		Thread2_sys(p->lchild, pre2);
		if (p->lchild == NULL)		//左孩子为空的话，指向他的上一个节点
		{
			p->ltag = 1;//标志，以便我们遍历容易遍历
			p->lchild = pre2;
		}
		if (pre2 && pre2->rchild == NULL)	//上一个节点右孩子为空，则指向现在这个节点
		{
			pre2->rtag = 1;//标志，以便我们遍历容易遍历
			pre2->rchild = p;
		}
		pre2 = p;
		Thread2_sys(p->rchild, pre2);
	}
}
void Thread2(bitree *t)
{
	bitree* pre2 = NULL;
	Thread2_sys(t, pre2);
	pre2->rtag = 1;
}
//根据一个节点，找到下一个节点
bitree *Inorder_next(bitree *p)
{
	if (p->rtag == 1)				// == 1 说明使我们加的一条线，不是原来二叉树有的
		return p->rchild;			// 只要是右边 rtag == 1 说明一定指向了他的下一个节点
	else
	{
		p = p->rchild;				// 走到这里来了，说明右边有孩子
		while (/*p && */p->ltag == 0)	// 那我们再次遍历他的左孩子，走到最低端，中序遍历嘛   如果最后一个节点设置了右孩子就不需要 p &&
			p = p->lchild;
		return p;
	}
}
//中序遍历
void Travel_order(bitree *t)
{
	while (t->ltag == 0)		//中序遍历，第一个节点，肯定是最左边的那个孩子
		t = t->lchild;
	while (t)
	{
		cout << t->data;
		t = Inorder_next(t);	//找到第一个就能找到下一个
	}
	cout << endl;
}
//////////////////////////////////////////////////////////////////////
////////////////////反着打印////////////////////////////////////////
bitree* Last(bitree* p)
{
	while (p->rtag != 1)
		p = p->rchild;
	return p;
}
bitree* Prev(bitree* p)
{
	if (p == NULL) return NULL;
	if (p->ltag == 1)
		return p->lchild;
	else
		return Last(p->lchild);
}
void resTravel_order(bitree *t)
{
	for (bitree *p = Last(pre); p != NULL; p = Prev(p))
	{
		cout << p->data << "  ";
	}
	cout << endl;
}
int main()
{
	bitree* root;
	root = create();
	Inorder(root);
	cout << endl << "----------看是否和上面中序遍历一样-----------" << endl;
	pre = root;
	Thread(root);
	Travel_order(root);

	bitree* root2 = create();
	Thread2(root2);
	Travel_order(root2);
	resTravel_order(root2);

	system("pause");
}
/*
其中：ltag=0 时lchild指向左子女；
ltag=1 时lchild指向前驱；
rtag=0 时rchild指向右子女；
rtag=1 时rchild指向后继；
*/
//输入：ABC@DE@$
//打印：BDAEC