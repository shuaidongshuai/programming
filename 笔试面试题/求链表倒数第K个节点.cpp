#include <iostream>
using namespace std;

typedef struct dong{
	char val;
	dong *next;
}Node;

/*无头结点*/
Node* create_NO_head()
{
	char ch;
	ch = getchar();
	Node *root = new (nothrow)Node;
	if (NULL == root)
		return NULL;
	if (ch == '#')
		return NULL;
	root->val = ch;
	Node *temp = root;
	Node *node;
	while ((ch = getchar()) != '#')
	{
		node = new Node;
		if (NULL == root)
			return NULL;
		node->val = ch;
		node->next = NULL;
		temp->next = node;
		temp = node;
	}
	return root;
}
Node *create_head_head()
{
	char ch;
	Node *root = new (nothrow)Node;
	if (NULL == root)
		return NULL;
	root->next = NULL;
	Node *node;
	while ((ch = getchar()) != '#')
	{
		node = new Node;
		node->val = ch;
		node->next = NULL;
		node->next = root->next;
		root->next = node;
	}
	return root;
}
void print(Node *n)
{
	if (n != NULL)
	{
		cout << n->val << endl;
		print(n->next);
	}
}
void print2(Node *n)
{
	n = n->next;
	if (n != NULL)
	{
		cout << n->val << endl;
		print2(n);
	}
}
/*
长度未知，求链表倒数第K个节点 要求时间复杂度为 O(n) 空间复杂度为 O(1)
*/
Node* last_K(Node *node, int k)
{
	Node *node_k = node;
	for (int i = 0; i<k - 1; i++)
	{
		if (node == NULL)
			return NULL;
		node_k = node_k->next;
	}
	while (node_k->next != NULL)
	{
		node_k = node_k->next;
		node = node->next;
	}
	return node;
}
/*
长度未知，求链表倒数第K个节点 要求时间复杂度为 O(n) 空间复杂度为 O(1)   第二种方法
*/
Node* last_K2(Node *node, int k)
{
	Node **a = new Node*[k];
	int i = 0;
	while (node != NULL)
	{
		*(a + i) = node;
		node = node->next;
		i = ++i % k;
	}
	return a[i];
}

int main()
{
	Node *node = create_NO_head();
	print(node);
	Node *node2 = create_NO_head();
	print(node2);

	cout << "k----------" << last_K(node, 3)->val << endl;
	cout << "k----------" << last_K2(node, 3)->val << endl;
	Node * node3 = mer(node, node2);
	print2(node3);
}
/*
13579#2468#
*/
