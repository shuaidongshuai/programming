/*
情况1. 节点只有left/right，没有parent指针，root已知

情况2. root未知，但是每个节点都有parent指针

情况3. 二叉树是个二叉查找树，且root和两个节点的值(a, b)已知


1.这个两种方法（1）找到某个节点，然后找父节点（并依次存入到数组中），然后另一个节点也依次找父节点（每找一次就遍历一下数组中是否有这个父节点）
			（2）方法一涉及到了循环，我们可以先找到这两个节点，然后依次找父节点，如果这个节点在父节点的右边就在string中 + "1" 左边就 + "0" 到时候从最后开始比较两个字符串，什么时候相等，那就是公共父节点
			（2）方法2是从情况3中得到的灵感，从根开始，如果这两个节点在根的两边，说明这个就是公共节点，否则继续
2.思路：从当前节点到root形成两条链表，我们要求的就是两个链表第一个公共节点

3.只要子节点数值在根的数值得两边，那么这个就是公共父节点（最简单的）
*/
#include <iostream>
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
/*没有处理没找到的情况，也就是不能乱给一个节点信息*/
BinaryTree findLowestParrent(BinaryTree root, BinaryTree a, BinaryTree b)
{
	if (root == NULL)
		return NULL;
	if (root == a || root == b)//只要找到一个节点就返回这个节点
		return root;
	BinaryTree left = findLowestParrent(root->leftchild, a, b);
	BinaryTree right = findLowestParrent(root->rightchild, a, b);
	if (left != NULL && right != NULL)//当左右节点都不为空的时候，说明找到了最近的公共父节点，利用的还是情况3的思路（从根节点一下，只要某个节点左右子树都包含要找的节点，说明这个就是他们的公共父节点）
		return root;
	return left != NULL ? left : right;//找到左边那一个节点就返回它的父节点（相当于利用递归依次返回了它的父节点），同理如果找到了右节点
	/*
	利用第一个根举例：如果左边右边同时右节点，那么返回的就是root（64行）
					  如果只有left不为空，right为空，那么返回left（这个left相当于又是另一个递归的root节点，依次重复）（始终能找到，left 和 right 同时存在的情况）
	*/
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
int main()
{
	ElemType *str1 = "ABDH##J##E##CF##G##";
	BinaryTree root = CreateTree2(str1);
	BinaryTree a = findNode(root, 'H');
	BinaryTree b = findNode(root, 'J');
	cout << a->data << endl;
	cout << b->data << endl;
	cout << findLowestParrent(root, a, b)->data << endl;

	cout << "---------------------------------------" << endl;
	BinaryTree a2 = findNode(root, 'E');
	BinaryTree b2 = findNode(root, 'J');
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

	system("pause");
}
/*								这就是我定义的这棵树
										A
								B				C
							D		E		F		G
						  H   J
*/