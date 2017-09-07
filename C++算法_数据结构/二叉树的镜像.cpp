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

void Mirror(Node *node)
{
	if(!node)
		return;
	Node *temp = node->left;
	node->left = node->right;
	node->right = temp;
	Mirror(node->left);
	Mirror(node->right); 
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
	Node *node1 = Create(str1);
	print(node1);
	cout<<endl<<"--------------------------"<<endl;
	Mirror(node1);
	print(node1);
}
