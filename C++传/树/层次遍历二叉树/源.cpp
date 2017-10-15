//给定一棵二叉树，要求分层遍历该二叉树，即从上到下按层次访问该树，每一层单独输出一行，每一层要求访问的顺序为从左到右。
//我们在遍历的过程中将该层节点的孩子节点压入一个队列，这样就可以实现从上到下一层一层地遍历该二叉树。
#include <iostream>
#include <queue>
using namespace std;

typedef struct NODE{
	char val;
	struct NODE *left, *right;
}Node, *Tree;

//先序创建
void createTree(Tree &t, char *&a)//注意这里我们必须用&引用，因为我们要改变传进来的root的地址（要为它分配内存）
{
	if (*a == ' ' || *a == NULL)
	{
		t = NULL;
		return;
	}
	t = new Node;
	t->val = *a;
	createTree(t->left, ++a);
	createTree(t->right, ++a);
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

void printByLevel(Tree t)
{
	Tree p;
	queue<Tree> q;
	q.push(t);
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		cout << p->val << " ";
		if (p->left)
			q.push(p->left);
		if (p->right)
			q.push(p->right);
	}
}

int main()
{
	char *a = "123  4  56";
	Tree t = new Node;
	createTree(t, a);
	preOrderY(t);
	cout << endl;
	printByLevel(t);

	system("pause");
}