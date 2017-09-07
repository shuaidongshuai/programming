#include <iostream>
#include <cstdlib>
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
int max(int a, int b);
int depth(Node *n)
{
	if (n == NULL)
		return 0;
	return max(depth(n->left) , depth(n->right)) + 1;
}
/*用于求某个节点的左右高度和+1*/
int sizeTree_sys(Node *node)
{
	if (node == NULL)
		return 0;

	int rootSize = depth(node->left) + depth(node->right) + 1;//求出这个根的左右最大高度并相加
	int leftSize = sizeTree_sys(node->left);//递归左孩子
	int rightSize = sizeTree_sys(node->right);//递归右孩子

	return max(max(rootSize, leftSize), rightSize);//选出左孩子size 右孩子size 和 根size哪个最大
}
void printPre(Node *node)
{
	if (node == NULL)
		return;
	cout << node->val << " ";
	printPre(node->left);
	printPre(node->right);
}

int main()
{
	char *a = "ABDF   EGH    C  ";
	Tree root = NULL;
	//先创建一棵树 
	createTree(root, a);
	printPre(root);
	cout << endl << "------------------------" << endl;
	cout << "深度：" << sizeTree_sys(root) << endl;

	system("pause");
	return 0;
}