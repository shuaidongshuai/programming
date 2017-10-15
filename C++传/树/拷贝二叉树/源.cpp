#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct NODE{
	int val;
	struct NODE *left;
	struct NODE *right;
	NODE(int val) :val(val), left(NULL), right(NULL){}
}Node, *Tree;
void create(Tree &p, int val)
{
	if (p == NULL)
		p = new Node(val);

	else
	{
		if (val < p->val)
			create(p->left, val);

		if (val > p->val)
			create(p->right, val);
	}
}
//先序遍历
void perOrder(Tree t)
{
	if (t == NULL)
	{
		return;
	}
	cout << t->val << "   ";
	perOrder(t->left);
	perOrder(t->right);
}
//拷贝二叉树
Tree copyTree(Tree t)
{
	Tree tLeft = NULL, tRight = NULL, tNode = NULL;//创建三个指针
	if (t->left)
		tLeft = copyTree(t->left);//左指针 进行递归遍历左节点
	else
		tLeft = NULL;			//直到某个节点的左节点为NULL
	if (t->right)				  
		tRight = copyTree(t->right);//右指针  进行递归遍历右节点
	else
		tRight = NULL;			//直到某个节点的右节点为NULL

	tNode = new Node(t->val);//拷贝这个树的root节点
	tNode->left = tLeft;	//拷贝这个树的Left节点
	tNode->right = tRight;	//拷贝这个树的Right节点

	return tNode;
}

int main()
{
	int a[20];
	Tree root = NULL;
	//先创建一棵树 
	for (int i = 0; i<10; i++){
		a[i] = rand() % 100;
		printf("%-5d", a[i]);
	}
	for (int i = 0; i<10; i++)
		create(root, a[i]);

	cout << endl << "先序遍历" << endl;
	perOrder(root);

	cout << endl << "下面进行拷贝" << endl;

	Tree cT = copyTree(root);
	perOrder(cT);

	cin.get();
}