#include <iostream>
#include <vector>
#include <stack>
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
//递归
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
//非递归
Node *Convert2(Node *node){
	if (!node)
		return NULL;
	stack<Node *> s;
	Node *root = NULL, *pre = NULL;
	while (!s.empty() || node){
		while (node){
			s.push(node);
			node = node->left;
		}
		node = s.top();
		s.pop();
		if (!root){
			root = pre = node;
			root->left = NULL;
		}
		else{
			node->left = pre;
			pre->right = node;
			pre = node;//注意 pre要跟上来
		}
		node = node->right;
	}
	return root;
}
///////////////////////////////测试//////////////////////////////////
void print(Node *node)
{
	if (node)
	{
		cout << node->val << " ";
		print(node->left);
		print(node->right);
	}
}
//递归
void test1(){
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
	cout << endl;
}
//非递归
void test2(){
	char *str1 = "421##3##865##7###";
	Node *node1 = Create(str1);
	cout << "--------------------------" << endl;
	Node *node = Convert2(node1);
	while (node){
		cout << node->val << " ";
		node = node->right;
	}
	cout << endl;
}
int main()
{
	test1();
	test2();
	system("pause");
}