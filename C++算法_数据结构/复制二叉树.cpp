#include <iostream>
#include <stack>
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
//µ›πÈ
Node* CopyTree(Node* oldNode){
	if(!oldNode)
		return NULL;
	Node *newNode = new Node;
	newNode->val = oldNode->val;
	newNode->left = CopyTree(oldNode->left);
	newNode->right = CopyTree(oldNode->right);
	return newNode; 
}
//∑«µ›πÈ
Node* CopyTree2(Node* oldNode){
	if(!oldNode)
		return NULL;
	stack<Node*> sold;
	stack<Node*> snew;
	Node* newNode = new Node;
	newNode->val = oldNode->val;
	sold.push(oldNode);
	snew.push(newNode);

	while(!sold.empty()){
		while(!snew.empty()){
			Node *nnew = snew.top(); snew.pop();
			Node *nold = sold.top(); sold.pop();
			Node *left = nold->left;
			Node *right = nold->right;
			if(left){
				nnew->left = new Node;
				nnew->left->val = left->val;
				sold.push(left);
				snew.push(nnew->left);
			}
			else{
				nnew->left = NULL;
			}
			if(right){
				nnew->right = new Node;
				nnew->right->val = right->val;
				sold.push(right);
				snew.push(nnew->right);
			}
			else{
				nnew->right = NULL;
			}
		}
	}
	return newNode;
} 
/////////////////////≤‚ ‘/////////////////////
void print(Node *node)
{
	if(node){
		cout<<node->val<<" ";
		print(node->left);
		print(node->right);
	}
}
void test1(){
	char *str1 = "123##4##2324##3###6##";
	Node *node1 = Create(str1);
	print(node1);
	cout<<endl<<"--------------------------"<<endl;
	Node *node2 = CopyTree(node1);
	print(node2);
}
void test2(){
	char *str1 = "123##4##2324##3###6##";
	Node *node1 = Create(str1);
	cout<<endl<<"--------------------------"<<endl;
	Node *node2 = CopyTree2(node1);
	print(node2);
}
int main(){
	test1();
	test2();
}
