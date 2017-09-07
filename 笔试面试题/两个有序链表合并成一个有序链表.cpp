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
/* 两个有序链表合并成一个有序链表   会带一个头结点*/
Node* mer(Node *first, Node *second)
{
	Node *root = new Node;
	Node *node = root;
	Node *temp;
	while (first != NULL && second != NULL)
	{
		if (first->val < second->val)
		{
			temp = first;
			first = first->next;			//**********注意：提前保存下一个节点，不然----- 
			node->next = temp;
			node = node->next;
		}
		else
		{
			temp = second;
			second = second->next;
			node->next = temp;
			node = node->next;
		}
	}
	while (first != NULL)
	{
		temp = first;
		first = first->next;
		node->next = temp;
		node = node->next;
	}
	while (second != NULL)
	{
		temp = second;
		second = second->next;
		node->next = temp;
		node = node->next;
	}
	return root;
}
/* 上面代码重复的太多了 */
void add(Node *&node, Node *&ad)
{
	Node *temp = ad;
	ad = ad->next;
	node->next = temp;
	node = node->next;
}
Node *mer2(Node *first, Node *second)
{
	Node *root = new Node;
	Node *node = root;
	while (first != NULL && second != NULL)
	{
		if (first->val < second->val)
			add(node,first);
		else
			add(node,second);
	}
	while (first != NULL)
		add(node,first);
	while (second != NULL)
		add(node,second);
	return root;
}

/* 别人的方法 递归*/
Node* SortedMerge(Node* a, Node* b)  
{  
    Node* result = NULL;  
      
    if(a == NULL)  
        return (b);  
    else if(b == NULL)  
        return (a);  
  
    if(a->val <= b->val)  
    {  
        result = a;  
        result->next = SortedMerge(a->next, b);  
    }  
    else  
    {  
        result = b;  
        result->next = SortedMerge(a, b->next);  
    }  
    return (result);  
}  

int main()
{
	Node *node = create_NO_head();
	print(node);
	Node *node2 = create_NO_head();
	print(node2);

cout<<"----------------------------------"<<endl;
//	Node * node4 = SortedMerge(node, node2);			//为什么要注释掉呢？   因为：我们已经改变了原来两个链表本身的结构了 
//	print(node4);
cout<<"----------------------------------"<<endl;
	Node * node3 = mer2(node, node2);
	print2(node3);
cout<<"----------------------------------"<<endl;
	print(node);
cout<<"----------------------------------"<<endl;
	print(node2);
}
/*
13579#2468#
*/
