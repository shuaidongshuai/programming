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
////////////////递归/////////////////////
void reverse_print(Node node){
	if(!node) return; 
	node = node->next;
	if(node == NULL)
		return;
	reverse_print(node);
	cout<<node->a<<"  ";
}
////////////////非递归///////////////////// 
void reverse_print2(Node head){
	if(!head || !head->next) return;
	Node flag = NULL;
	Node node = head->next;//带头结点 
	while(flag != head->next){
		while(node->next != flag)
			node = node->next;
		cout<<node->a<<"  ";
		flag = node;
		node = head->next;
	}
}
//abcdefg$ 
int main(){
	Node root = create();
	cout<<"////////////////正常/////////////////////"<<endl; 
	print(root);
	cout<<"////////////////递归/////////////////////"<<endl; 
	reverse_print(root);
	cout<<endl;
	cout<<"////////////////非递归/////////////////////"<<endl; 
	reverse_print2(root);
}
