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
//递归---利用先序遍历的思想
void Mirror(Node *node){
	if(!node)
		return;
	Node *temp = node->left;
	node->left = node->right;
	node->right = temp;
	Mirror(node->left);
	Mirror(node->right); 
}
//非递归---利用层次遍历的思想
void Mirror2(Node *node){
	if(!node)
		return;
	stack<Node *> s;
	s.push(node);
	while(!s.empty()){
		node = s.top();
		s.pop();
		Node *l = node->left,*r = node->right;//用两个变量来交换位置 
		node->left = r;
		node->right = l;
		if(l) s.push(l);
		if(r) s.push(r);//注意： 下面这个if不能写成 else if  又弄错一次 
	}
}
/////////////////////测试/////////////////////
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
	Mirror(node1);
	print(node1);
}
void test2(){
	char *str1 = "123##4##2324##3###6##";
	Node *node1 = Create(str1);
	cout<<endl<<"--------------------------"<<endl;
	Mirror2(node1);
	print(node1);
}
int main(){
	test1();
	test2();
}
