#include <iostream>
using namespace std;
//交换一个链表相邻两个节点 1->2->3->4    2->1->4->3
struct Node{
	char val;
	Node *next;
	Node(char c):val(c),next(NULL){}
};
Node *CreateList(char *str){
	if(!str || *str == 0)
		return NULL;
	Node *node = new Node(*str++);
	node->next = CreateList(str);
	return node; 
}
void print(Node *head){
	if(head){
		cout<<head->val<<" ";
		print(head->next);
	}
}

void SysSwapCloseNode(Node *head, Node *node1, Node *node2){
	if(!head || !node1 || !node2)
		return;
	node1->next = node2->next;
	node2->next = node1;
	head->next = node2;
	if(node1->next && node1->next->next){
		SysSwapCloseNode(node1, node1->next, node1->next->next);
	}
}
void SwapCloseNode(Node *&head){
	if(!head || !head->next){
		return;
	}
	//由于无头结点，所以需要先交换前两个node
	Node *second = head->next;
	head->next = second->next;
	second->next = head;
	if(head->next && head->next->next){
		SysSwapCloseNode(head, head->next, head->next->next);
	}
	head = second;//头结点替换
}

int main(){
	Node *head = CreateList("hello dong");
	print(head);
	cout<<endl;
	SwapCloseNode(head);
	print(head);
}
/*
h e l l o   d o n g
e h l l   o o d g n
*/
