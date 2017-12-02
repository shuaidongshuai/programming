#ifndef TREE
#define TREE
#include <iostream>
using namespace std;
typedef struct NODE{
	char val;
	struct NODE *left, *right;
	NODE(int val) :val(val), left(NULL), right(NULL){}
}Node, *Tree;

void createTree(Tree &t, char a[], int &i);
//递归中序遍历
void inOrderY(Tree t);
//递归先序遍历
void preOrderY(Tree t);
//递归后序遍历
void postOrderY(Tree t);
#endif