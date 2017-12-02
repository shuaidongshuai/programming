#include "Tree.h"
void createTree(Tree &t, char a[], int &i)//注意这里我们必须用&引用，因为我们要改变传进来的root的地址（要为它分配内存）
{
	if (i > 9 || a[i] == ' ')
	{
		t = NULL;
		return;
	}
	cout << a[i] << "+++" << endl;

	t = new Node(a[i]);
	createTree(t->left, a, ++i);
	createTree(t->right, a, ++i);
}
//递归中序遍历
void inOrderY(Tree t)
{
	if (!t)
		return;
	inOrderY(t->left);
	cout << t->val << "   ";
	inOrderY(t->right);
}
//递归先序遍历
void preOrderY(Tree t)
{
	if (!t)
		return;
	cout << t->val << "   ";
	preOrderY(t->left);
	preOrderY(t->right);
}
//递归后序遍历
void postOrderY(Tree t)
{
	if (!t)
		return;
	postOrderY(t->left);
	postOrderY(t->right);
	cout << t->val << "   ";
}
