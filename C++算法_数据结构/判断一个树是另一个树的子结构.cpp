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
bool Tree1HasTree2(Node *node1,Node *node2)
{
	if(!node2)
		return true;
	else if(!node1)
		return false;
	else if(node1->val != node2->val)
		return false;
	return Tree1HasTree2(node1->left,node2->left) && Tree1HasTree2(node1->right,node2->right);
}
bool HasSubtree(Node *node1,Node *node2)
{
	bool res = false;
	if(node1 && node2)
	{
		if(node1->val == node2->val)
			res = Tree1HasTree2(node1,node2);
		if(!res)
			res = HasSubtree(node1->left,node2);
		if(!res)
			res = HasSubtree(node1->right,node2);
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
	char *str2 = "23##6##";
	Node *node1 = Create(str1);
	print(node1);
	cout<<endl<<"--------------------------"<<endl;
	Node *node2 = Create(str2);
	print(node2);
	cout<<endl<<"--------------------------"<<endl;
	cout<<HasSubtree(node1,node2)<<endl;
 } 
