/*
情况1. 节点只有left/right，没有parent指针，root已知

情况2. root未知，但是每个节点都有parent指针

情况3. 二叉树是个二叉查找树，且root和两个节点的值(a, b)已知


1.这个两种方法（1）找到某个节点，然后找父节点（并依次存入到数组中），然后另一个节点也依次找父节点（每找一次就遍历一下数组中是否有这个父节点）
			（2）方法一涉及到了循环，我们可以先找到这两个节点，然后依次找父节点，如果这个节点在父节点的右边就在string中 + "1" 左边就 + "0" 到时候从最后开始比较两个字符串，什么时候相等，那就是公共父节点
			（3）方法2是从情况3中得到的灵感，从根开始，如果这两个节点在根的两边，说明这个就是公共节点，否则继续
			（4）找到两个节点的路径，然后求两条链公共最长的节点，就是公共父节点

2.思路：从当前节点到root形成两条链表，我们要求的就是两个链表第一个公共节点

3.只要子节点数值在根的数值得两边，那么这个就是公共父节点（最简单的）
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef char ElemType;
#define  END '#'

typedef struct BtNode  // BinaryTreeNode
{
	//BtNode *parent;
	BtNode *rightchild;
	BtNode *leftchild;
	ElemType data;
}BtNode, *BinaryTree;

BtNode * _Buynode()
{
	BtNode *s = (BtNode*)malloc(sizeof(BtNode));
	if (NULL == s) exit(1);
	memset(s, 0, sizeof(BtNode));
	return s;
}

BtNode * CreateTree2(ElemType *&str)
{
	BtNode *s = NULL;
	if (*str != END)
	{
		s = _Buynode();
		s->data = *str;
		s->leftchild = CreateTree2(++str);
		s->rightchild = CreateTree2(++str);
	}
	return s;
}
/* 没有处理没找到的情况，也就是不能乱给一个节点信息  但是解决了其中一个是另一个父节点的情况 */
//从根开始，如果这两个节点在根的两边，说明这个就是公共节点，否则继续
BinaryTree findLowestParrent(BinaryTree root, BinaryTree a, BinaryTree b){
	if (root == NULL)
		return NULL;
	if (root == a || root == b)//只要找到一个节点就返回这个节点
		return root;
	BinaryTree left = findLowestParrent(root->leftchild, a, b);
	BinaryTree right = findLowestParrent(root->rightchild, a, b);
	if (left != NULL && right != NULL)//当左右节点都不为空的时候，说明找到了最近的公共父节点，利用的还是情况3的思路（从根节点一下，只要某个节点左右子树都包含要找的节点，说明这个就是他们的公共父节点）
		return root;
	return left != NULL ? left : right;//左边如果有节点，返回左边。这也解决了两个节点都在左边的情况（一个节点是另一个的父节点）返回的依然是这个父节点
}
/*解决了不存在的节点问题  而且变得通用，多叉树思路也是这样*/
//找到两个节点的路径，然后求两条链公共最长的节点，就是公共父节点
bool findPath(BinaryTree root, BinaryTree a, vector<BinaryTree> &v){
	if (!root || !a)
		return false;
	if (root == a){		//找到了
		v.push_back(root);
		return true;
	}
	v.push_back(root);
	bool res = false;
	if (root->leftchild)//去左边找
		res = findPath(root->leftchild, a, v);
	if (!res && root->rightchild)//如果左边没有找到就去右边
		res = findPath(root->rightchild, a, v);
	if (!res)//右边也没找到
		v.pop_back();
	return res;
}
BinaryTree findLowestParrent2(BinaryTree root, BinaryTree a, BinaryTree b){
	vector<BinaryTree> v1;
	vector<BinaryTree> v2;
	findPath(root, a, v1);
	findPath(root, b, v2);
	int len = v1.size() < v2.size() ? v1.size() : v2.size();
	for (int i = len - 1; i >= 0; --i){
		if (v1[i] == v2[i])
			return v1[i];
	}
	return NULL;
}
/*-----------------------下面的代码就是测试了---------------------------*/
BinaryTree findNode(BinaryTree root, char ch)
{
	BinaryTree tree = NULL;
	if (root != NULL)
	{
		if (ch == root->data)
			return root;
		tree = findNode(root->leftchild, ch);
		if (tree == NULL)
			tree = findNode(root->rightchild, ch);
	}
	return tree;
}
void test1(){
	cout << "----------------方法1-----------------------" << endl;
	ElemType *str1 = "ABDH##J##E##CF##G##";
	BinaryTree root = CreateTree2(str1);
	BinaryTree a = findNode(root, 'H');
	BinaryTree b = findNode(root, 'J');
	cout << a->data << endl;
	cout << b->data << endl;
	cout << findLowestParrent(root, a, b)->data << endl;

	cout << "---------------------------------------" << endl;
	BinaryTree a2 = findNode(root, 'B');
	BinaryTree b2 = findNode(root, 'E');
	cout << a2->data << endl;
	cout << b2->data << endl;
	cout << findLowestParrent(root, a2, b2)->data << endl;

	cout << "----------------看一下没找到的情况-----------------------" << endl;
	BinaryTree a3 = new BtNode;
	a3->data = 'M';
	a3->leftchild = a3->rightchild = NULL;
	BinaryTree c3 = findLowestParrent(root, a3, b2);//a3不在里面，但是我们返回了b2，因为b2存在
	if (c3)
		cout << c3->data << endl;
	else
		cout << "没找到" << endl;
}
void test2(){
	cout << "----------------方法2-----------------------" << endl;
	ElemType *str1 = "ABDH##J##E##CF##G##";
	BinaryTree root = CreateTree2(str1);
	BinaryTree a = findNode(root, 'H');
	BinaryTree b = findNode(root, 'J');
	cout << a->data << endl;
	cout << b->data << endl;
	cout << findLowestParrent2(root, a, b)->data << endl;

	cout << "---------------------------------------" << endl;
	BinaryTree a2 = findNode(root, 'B');
	BinaryTree b2 = findNode(root, 'E');
	cout << a2->data << endl;
	cout << b2->data << endl;
	cout << findLowestParrent2(root, a2, b2)->data << endl;

	cout << "----------------看一下没找到的情况-----------------------" << endl;
	BinaryTree a3 = new BtNode;
	a3->data = 'M';
	a3->leftchild = a3->rightchild = NULL;
	BinaryTree c3 = findLowestParrent2(root, a3, b2);//a3不在里面，但是我们返回了b2，因为b2存在
	if (c3)
		cout << c3->data << endl;
	else
		cout << "没找到" << endl;
}
int main()
{
	test1();
	test2();
	system("pause");
}
/*								这就是我定义的这棵树
										A
								B				C
							D		E		F		G
						  H   J
*/