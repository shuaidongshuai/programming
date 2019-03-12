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
	//这样进行new判断比较好 
	//	try
	//	{
	//		Node *root = new Node;
	//	}
	//	catch(const bad_alloc &e)
	//	{
	//		return -1;
	//	}
	//简化
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
void print(Node *n)
{
	if (n != NULL)
	{
		cout << n->val << endl;
		print(n->next);
	}
}

/*递归方式*/ 
Node *reverse_sys(Node *pre, Node *cur)
{
	Node *t = NULL;
	if (cur != NULL)
	{
		t = reverse_sys(cur, cur->next);
		cur->next = pre;
		pre->next = NULL;
	}
	else
		t = pre;
	return t;
}
void reverse(Node *&node)
{
	node = reverse_sys(node, node->next);
}
/*第二种方法  简单点*/
void reverse_sys2(Node *cur, Node *&head)
{
	if(cur->next == NULL)
	{
		head = cur;
		return;
	}
	Node *next = cur->next;
	reverse_sys2(next,head);
	next->next = cur;
	cur->next = NULL;
}
void reverse2(Node *&node)
{
	reverse_sys2(node, node);
}

/*非递归实现*/
void reverse3(Node *&node)
{
	Node *temp;
	Node *p = node;
	node = node->next;
	p->next = NULL;
	while(node->next)
	{
		temp = node->next;
		node->next = p;
		p = node;
		node = temp;
	}
	node->next = p;
}

/*带头结点的*/
Node *create_head()
{
	char ch;
	Node *root = new (nothrow)Node;
	if (NULL == root)
		return NULL;
	Node *temp = root;
	Node *node;
	while ((ch = getchar()) != '#')
	{
		node = new (nothrow) Node;
		if (NULL == root)
			return NULL;
		node->val = ch;
		node->next = NULL;
		temp->next = node;
		temp = node;
	}
	return root;	
}
void print2(Node* node)
{
	node = node->next;
	if(node)
	{
		cout<<node->val<<endl;
		print(node->next);
	}
}

/*递归方式*/ 
void reverse_sys4(Node *cur, Node *&head)
{
	if(cur->next == NULL)
	{
		head->next = cur;					//改动的地方************* 
		return;
	}
	Node *next = cur->next;
	reverse_sys4(next,head);
	next->next = cur;
	cur->next = NULL;
}
void reverse4(Node *&node)
{
	reverse_sys4(node->next, node);			//改动的地方************* 
}

/*非递归实现*/
void reverse5(Node *&head)				//改动的地方*************  
{
	Node *node = head;					//改动的地方************* 
	node = node->next;					//改动的地方************* 
	Node *temp;
	Node *p = node;
	node = node->next;
	p->next = NULL;
	while(node->next)
	{
		temp = node->next;
		node->next = p;
		p = node;
		node = temp;
	}
	node->next = p;
	head->next = node;					//改动的地方************* 
}
int main()
{
	Node *node = create_head();
	print2(node);
	reverse5(node);
	print2(node);
}
