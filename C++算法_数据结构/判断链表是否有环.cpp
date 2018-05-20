#include <iostream>
#include <cstring>
using namespace std;
//注意：和面试官讨论 一个节点算不算环？ 按理来说应该算 
struct Node{
	int val;
	Node *next;
};
Node *create(){
	Node *nodes = new Node[5];
	for (int i = 1; i < 5; ++i){
		nodes[i - 1].next = &nodes[i];
		nodes[i - 1].val = i;
		nodes[i].next = NULL;
	}
	nodes[4].val = 5;
	return nodes;
}
void print(Node *node){
	int i = 1;
	while(i < 10 && node){
		cout<< node->val <<endl;
		node = node->next;
		++i; 
	}
}
bool HaveRoll(Node *node){
	Node *n1,*n2;
	n1 = n2 = node;
	do{
		if(!n2)
			return false;
		n1 = n1->next;
		n2 = n2->next;
		if(!n2)
			return false;
		n2 = n2->next;
	}while(n1 != n2);
	return true;
}
int main(){
	Node *node = create();
	print(node);
	cout<<"--------判断是否有环-----------"<<endl;	
	cout<<HaveRoll(node)<<endl;
	cout<<"---------改成有环----------"<<endl;
	node[4].next = &node[2];
	cout<<HaveRoll(node)<<endl;
}
