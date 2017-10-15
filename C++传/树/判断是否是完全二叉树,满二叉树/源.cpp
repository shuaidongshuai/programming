#include <queue>
#include <iostream>
#include <stack>
using namespace std;

template<class _Ty>
const _Ty & Max(const _Ty &a, const _Ty &b)
{
	return a>b ? a : b;
}

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

/*完全二叉树*/
bool Is_Comp_BinaryTree(BtNode *p)
{
	queue<BtNode *> q;
	q.push(p);
	bool tag = 0;//用于标识是否出现第一个空孩子
	while (!q.empty())
	{
		p = q.front();
		q.pop();
		if (p->leftchild != NULL)
		{
			if (tag)
				return false;
			q.push(p->leftchild);
		}
		else
		{
			tag = 1;
		}
		if (p->rightchild != NULL)
		{
			if (tag)
				return false;
			q.push(p->rightchild);
		}
		else
		{
			tag = 1;
		}
	}
	return true;
}
/*判断满二叉树在网上也没有找到具体的代码，自己又两种方法1,先求出高度和节点数，满二叉树  2^高度 - 1 = 节点数
													方法2,见如下代码  利用的是求深度的思想*/
int isEqualHight_sys(BinaryTree root,bool &tag)
{
	if (!root) return 0;
	int leftHeight = isEqualHight_sys(root->leftchild, tag);
	int rightHeight = isEqualHight_sys(root->rightchild, tag);
	if (leftHeight != rightHeight)
		tag = true;
	return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
bool isEqualHight(BinaryTree root)
{
	bool tag = false;//所以我利用了标志位，只要有一次不等高那么我就修改标志位，就不存在下面这样的bug了
	isEqualHight_sys(root, tag);
	if (tag) return false;
	return true;
}
/////////////////////////////////////////////////////////////////////
int max(int a, int b)
{
	return a > b ? a : b;
}
int getDepth(BinaryTree root)
{
	if (!root) return 0;
	return max(getDepth(root->leftchild), getDepth(root->rightchild)) + 1;//返回左子树，和右子树最高的，然后 + 1（根）
}
bool isEqualHight2(BinaryTree root)
{
	return (root == NULL || 
		getDepth(root->leftchild) == getDepth(root->rightchild) && 
		isEqualHight2(root->leftchild) && isEqualHight2(root->rightchild));
}
/*最开始是像下面这样写的，不过后来想想有问题，当左右两边不等高，but左边出现两次不等高，那么就会产生false = false 返回左边就变成了true == 右边true*/
//bool isEqualHight(BinaryTree root)
//{
//	if (!root) return true;
//	int leftHeight = isEqualHight(root->leftchild);
//	int rightHeight = isEqualHight(root->rightchild);
//	if (leftHeight != rightHeight)//如果左子树高度不等于右子树，那么高度加1
//		return false;
//	return true;
//}
/*左右子树深度不超过1*/
bool IsBalanced(BinaryTree root)
{
	if (!root)
		return true;
	int leftDepth = getDepth(root->leftchild);
	int rightDepth = getDepth(root->rightchild);
	int diff = leftDepth - rightDepth;
	if (diff > 1 || diff < -1)
		return false;
	return IsBalanced(root->leftchild) && IsBalanced(root->rightchild);
}
/*上面这样求会多很多无畏的求高，我们可以后序遍历到最下面，然后把高度记录下来*/
bool IsBalanced2(BinaryTree root,int &depth)
{
	if (!root)
		return true;
	int leftDepth, rightDepth;
	if (IsBalanced2(root, leftDepth) && IsBalanced2(root, rightDepth))//先进行后序遍历的递归操作，第一次进来是最左边那个节点
	{
		//判断是否高度差1
		int diff = leftDepth - rightDepth;
		if (diff >= -1 || diff <= 1)
		{
			depth = (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;//高度加1，因为是引用，会返回给上一层
			return true;
		}
	}
	return false;
}
bool IsBalanced2(BinaryTree root)
{
	int dep = 0;
	return IsBalanced2(root,dep);
}
void prePrint(BinaryTree root)
{
	if (root)
	{
		cout << root->data << "\t";
		prePrint(root->leftchild);
		prePrint(root->rightchild);
	}
}

void main()
{
	ElemType *str1 = "ABDH###E##CF##G##";
	ElemType *str2 = "ABDH###E1###CF##G##";
	ElemType *str3 = "ABD##E##CF##G##";
	ElemType *str4 = "ABDH##J##E##CF##G##";
	BinaryTree root = CreateTree2(str1);
	prePrint(root);
	cout << endl << "str1 完全二叉树：" << Is_Comp_BinaryTree(root) << endl;
	cout << endl << "--------------------------------" << endl;

	BinaryTree root2 = CreateTree2(str2);
	prePrint(root2);
	cout << endl << "str2 完全二叉树：" << Is_Comp_BinaryTree(root2) << endl;
	cout << endl << "--------------------------------" << endl;

	BinaryTree root3 = CreateTree2(str3);
	prePrint(root3);
	cout << endl << "str3 满二叉树：" << isEqualHight(root3) << endl;
	cout << endl << "str3 满二叉树2：" << isEqualHight2(root3) << endl;
	cout << endl << "--------------------------------" << endl;

	BinaryTree root4 = CreateTree2(str4);
	prePrint(root4);
	cout << endl << "str4 满二叉树：" << isEqualHight(root4) << endl;
	cout << endl << "str4 满二叉树2：" << isEqualHight2(root4) << endl;
	cout << endl << "--------------------------------" << endl;

	system("pause");
}