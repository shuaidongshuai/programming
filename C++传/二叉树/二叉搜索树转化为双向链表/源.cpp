#include <iostream>
#include <vector>
using namespace std;

typedef struct NODE{
	char val;
	struct NODE *left, *right;
}Node, *Tree;

Node *Create(char *&str)
{
	if (!str || !*str || '#' == *str)
		return NULL;
	Node *node = new Node;
	node->val = *str;
	node->left = Create(++str);
	node->right = Create(++str);
	return node;
}
//left在双向链表中指向上一个，right指向下一个
void Convert(Node *node, Node *&pre)
{
	if (!node)
		return;
	//和中序递归遍历是一样的，先向左递归
	if (node->left)
		Convert(node->left, pre);
	//把最左边的节点，指向上一个节点
	node->left = pre;
	//pre的下一个节点也是node，所以如果pre存在那么需要指向node
	if (pre)
		pre->right = node;
	//把上一个节点挪到这个节点
	pre = node;
	//然后再递归右边
	if (node->right)
		Convert(node->right, pre);
}

Node *Convert(Node *node)
{
	if (!node)
		return NULL;
	Node *pre = NULL;
	Convert(node, pre);

	//返回链表的头
	while (pre->left)
		pre = pre->left;
	return pre;
}
void print(Node *node)
{
	if (node)
	{
		cout << node->val << " ";
		print(node->left);
		print(node->right);
	}
}
int main()
{
	char *str1 = "421##3##865##7###";
	Node *node1 = Create(str1);
	print(node1);
	cout << endl << "--------------------------" << endl;
	Node *node = Convert(node1);
	while (node)
	{
		cout << node->val << " ";
		node = node->right;
	}
	system("pause");
}