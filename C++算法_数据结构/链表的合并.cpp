#include <iostream>
#include <cstring>
using namespace std;

typedef struct Node
{
	char ch;
	Node *next;
}Node;

//递归 
Node *create(char *str)
{
	if(!str || !*str) return NULL;
	
	Node *node = new Node;
	node->ch = *str;
	node->next = create(str+1); 
	return node;
}

//递归合并
Node *Merge(Node *node1,Node *node2)
{
	if(!node1) 
		return node2;
	else if(!node2) 
		return node1;
	
	Node *newNode;
	if(node1->ch < node2->ch)
	{
		newNode = node1;
		newNode->next = Merge(node1->next,node2);
	}
	else
	{
		newNode = node2;
		newNode->next = Merge(node1,node2->next);
	}
	return newNode;
}
//非递归合并
Node *Merge2(Node *node1,Node *node2)
{
	if(!node1)
		return node2;
	else if(!node2)
		return node1;
	
	Node *root,*pre;
	if(node1->ch < node2->ch)
	{
		root = node1;
		node1 = node1->next;
	}
	else
	{
		root = node2;
		node2 = node2->next;
	}
	pre = root;
	while(node1 && node2)
	{
		if(node1->ch < node2->ch)
		{
			pre->next = node1;
			node1 = node1->next;
		}
		else
		{
			pre->next = node2;
			node2 = node2->next;
		}
		pre = pre->next;
	}
	if(!node1)
		pre->next = node2;
	else if(!node2)
		pre->next = node1;
	return root;
} 
void print(Node *root)
{
	while (root != NULL)
	{
		cout << root->ch<<" ";
		root = root->next;
	}
	cout << endl;
}
int main()
{
	char *str1 = "13579ac";
	char *str2 = "246788b";
	Node *node1 = create(str1);
	Node *node2 = create(str2);
	//Node *node3 = Merge(node1,node2);
	Node *node3 = Merge2(node1,node2);
	print(node3);
}
