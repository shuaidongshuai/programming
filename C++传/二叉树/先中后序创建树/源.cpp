#include <iostream>
#include <cstdlib>
#include <stack>
using namespace std;

typedef struct NODE{
	char val;
	struct NODE *left, *right;
}Node, *Tree;

//先序创建
void createTreeA(Tree &t, char a[], int &i)//注意这里我们必须用&引用，因为我们要改变传进来的root的地址（要为它分配内存）
{
	if (i > 9 || a[i] == ' ')
	{
		t = NULL;
		return;
	}

	t = new Node;

	t->val = a[i];
	createTreeA(t->left, a, ++i);
	createTreeA(t->right, a, ++i);
}
//中序创建
void createTreeB(Tree &t, char a[], int &i)//注意这里我们必须用&引用，因为我们要改变传进来的root的地址（要为它分配内存）
{
	int ii = i;
	if (i > 9 || a[i] == ' ')
	{
		t = NULL;
		return;
	}

	t = new Node;


	createTreeB(t->left, a, ++i);
	t->val = a[ii];
	createTreeB(t->right, a, ++i);
}
//后序创建
void createTreeC(Tree &t, char a[], int &i)
{
	int ii = i;
	if (i > 9 || a[i] == ' ')
	{
		t = NULL;
		return;
	}

	t = new Node;

	createTreeC(t->left, a, ++i);
	createTreeC(t->right, a, ++i);
	t->val = a[ii];
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
//递归中序遍历
void inOrderY(Tree t)
{
	if (!t)
		return;
	inOrderY(t->left);
	cout << t->val << "   ";
	inOrderY(t->right);
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
int main()
{
	//这种创建树的方法也叫作#创建法，我把#换成了空格   先中后创建出来的树都是一样的
	char a[] = { '1', '2', '3', ' ', ' ', '4', ' ', ' ', '5', '6' };//注意这里要两个空格，因为左右子树都需要NULL
	int i = 0, ii = 0, iii = 0;
	Tree rootA = NULL;
	Tree rootB = NULL;
	Tree rootC = NULL;

	//先序创建
	createTreeA(rootA, a, i);
	cout << "递归先序遍历" << endl;
	preOrderY(rootA);
	cout << endl << "递归中序遍历" << endl;
	inOrderY(rootA);
	cout << endl << endl << "递归后序遍历" << endl;
	postOrderY(rootA);

	cout << endl << "-------------------" << endl;

	//中序创建
	createTreeB(rootB, a, ii);
	cout << endl << "递归中序遍历" << endl;
	inOrderY(rootB);
	
	//后序创建
	createTreeB(rootC, a, iii);
	cout << endl << endl << "递归后序遍历" << endl;
	postOrderY(rootC);


	

	cin.get();
	return 0;
}