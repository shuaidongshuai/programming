#include <iostream>
#include <cstring>
using namespace std;

typedef struct NODE{
	char val;
	struct NODE *left, *right;
	NODE(char val) :val(val), left(NULL), right(NULL){}
}Node, *Tree;

bool addNode(Tree &t, char a)
{
	if (!t)
	{
		t = new Node(a);
		return true;
	}
	if (a < t->val)
		addNode(t->left, a);
	else if (a > t->val)
		addNode(t->right, a);
	else
		return false;
	return true;
}
Node *create(char *s)
{
	int len = strlen(s);
	Node *root = NULL;
	for (int i = 0; i < len; i++)
	{
		cout << addNode(root, s[i]) << " ";
	}
	cout << endl;
	return root;
}
void print(Node *node)
{
	if (node)
	{
		print(node->left);
		cout << node->val << " ";
		print(node->right);
	}
}
void reversePrint(Node *node)
{
	if (node)
	{
		reversePrint(node->right);
		cout << node->val << " ";
		reversePrint(node->left);
	}
}
int main()
{
	char *a = "4213657";
	Node *root = create(a);
	print(root);
	cout << endl;
	reversePrint(root);
	getchar();
}