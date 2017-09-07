#include<iostream>
using namespace std;

typedef struct Node
{
	char val;
	Node *left,*right;
}Node;

Node *Create(char *&str)
{
	if(!str || !*str || '#' == *str)
		return NULL;
	Node *node = new Node;
	node->val = *str;
	node->left = Create(++str);
	node->right = Create(++str);
	return node;
}
//当前节点值相等，并且左孩子的值 == 右孩子的值    或者都为空 
bool isIdentical(Node *node1,Node *node2)
{
	bool res = false;
	if(!node1 && !node2)
		res = true;
	else if(node1 && node2 && node1->val == node2->val)
	{
		res = isIdentical(node1->left,node2->left);
		if(res)
			res = isIdentical(node1->right,node2->right);
	}
	return res;
}
void print(Node *node)
{
	if(node)
	{
		cout<<node->val<<" ";
		print(node->left);
		print(node->right);
	}
}
int main()
{
	char *str1 = "123##4##2324##3###6##";
	char *str2 = "123##4##2324##3###6##";
	Node *node1 = Create(str1);
	print(node1);
	cout<<endl<<"--------------------------"<<endl;
	Node *node2 = Create(str2);
	print(node2);
	cout<<endl<<"--------------------------"<<endl;
	cout<<isIdentical(node1,node2)<<endl;
 } 
