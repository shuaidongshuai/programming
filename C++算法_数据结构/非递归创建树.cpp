#include<iostream>
using namespace std;

typedef struct dong{
	struct dong *l;
	struct dong *r;
	char data;
}Node;
//非递归创建树 
Node* initTree()
{
	Node* container[32];
	int front, rear;
	char c;
	front = rear = 0;
	Node *node;

	if ('$' == (c = getchar()))
		return NULL;
	node = new Node;
	node->data = c;
	node->l = NULL;
	node->r = NULL;
	container[front] = node;
	while ('$' != (c = getchar()))
	{
		if ('#' == c)
			node = NULL;
		else
		{
			node = new Node;
			node->data = c;
			node->l = NULL;
			node->r = NULL;
		}
		container[++rear] = node;
		if (!container[front])
			front++;
		if (1 == rear % 2)
			container[front]->l = node;
		else
			container[front++]->r = node;
	}
	return container[0];
}

//先序遍历
void preOrder(Node* node)
{
	if (!node)
		return;

	cout << node->data << "  ";
	preOrder(node->l);
	preOrder(node->r);
}

int main()
{
	Node* root = initTree();
	preOrder(root);
}
//    abd#ce#$
