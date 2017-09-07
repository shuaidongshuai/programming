#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

typedef struct Dong{
	char str[20];
	struct Dong *next;
}*Node, Dong;

Node init()
{
	Node root = new Dong;
	Node tNode = root;
	Node node;
	char str[20];
	cin >> str;
	while (*str != '$')
	{
		node = new Dong;
		strcpy(node->str, str);
		node->next = NULL;
		tNode->next = node;
		tNode = node;
		cin >> str;
	}
	return root;
}
void print(Node root)
{
	cout << "-------------------------" << endl;
	root = root->next;
	while (root != NULL)
	{
		cout << root->str << endl;
		root = root->next;
	}
	cout << "-------------------------" << endl;
}
/////////////////////////////递归//////////////////////////////////////
Node sys_reverse(Node pre, Node cur)
{
	Node Rnode = NULL;
	if (cur)
	{
		Rnode = sys_reverse(cur, cur->next);
		cur->next = pre;
	}
	else
	{
		Rnode = pre;//返回最后一个节点
	}
	return Rnode;
}

void reverse(Node root)
{
	if (!root)
		return;
	Node node = sys_reverse(root, root->next);
	root->next->next = NULL;					//*********注意：这里需要把除了头结点的第一个节点next赋值为NULL，不然打印就没有结束条件了
	root->next = node;//还需要把头结点和“原链表”的最后一个节点相连
}
/////////////////////////////非递归//////////////////////////////////////
void reverse2(Node root)
{
	if(!root) return;
	Node node = root->next;
	Node pre = NULL,nextNode;
	while(node)
	{
		nextNode = node->next;
		node->next = pre;
		pre = node;
		node = nextNode;
	}
	root->next = pre;
}

int main()
{
	Node root = init();
	print(root);
	reverse(root);
	print(root);
	reverse2(root);
	print(root);
}
/*
nice
to
meet
you
$
*/
