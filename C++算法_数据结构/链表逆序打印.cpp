#include <iostream>

using namespace std;

typedef struct dong{
	char a;
	struct dong *next;
}*Node, No;


void insert(Node root, Node node)
{
	if (node == NULL)
		return;
	node->next = root->next;
	root->next = node;
}

Node create()
{
	Node root = new No;
	root->next = NULL;
	root->a = '#';
	char ch;
	while ((ch = getchar()) != '$')
	{
		Node node = new No;
		node->a = ch;
		insert(root, node);
	}
	return root;
}

void print(Node l)
{
	l = l->next;
	while (l != NULL)
	{
		cout << l->a << "  ";
		l = l->next;
	}
	cout << endl;
}

void reverse_print(Node node)
{
	node = node->next;
	if(node == NULL)
		return ;
	reverse_print(node);
	cout<<node->a<<"  ";
}
void rever_print2(Node node)
{
	Node temp = node;
	Node temp2 = NULL;
	while(temp2 != node)
	{
		while(temp != temp2)
		{
			temp2 = temp;
			temp = temp->next;
		}
		cout<<temp2->a<<"   ";
	}
}

int main()
{
	Node root = create();
	print(root);
	reverse_print(root);
	cout<<endl;
	reverse_print(root);
}
