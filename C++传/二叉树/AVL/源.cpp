#include<iostream>
#include<stack>
#include<queue>
using namespace std;

template<class _Ty>
class AVLTree
{
protected:
	struct AVLNode
	{
		AVLNode *parent;
		AVLNode *leftchild;
		AVLNode *rightchild;
		int      balance; // -1 0  1
		_Ty      key;
	};
private:
	AVLNode *root;
public:
	AVLTree() :root(NULL) {}
	~AVLTree() {}
	static AVLNode* _Buynode()
	{
		return new AVLNode;
	}
	static int depth(AVLNode *&ptr)
	{
		if (!ptr) return 0;
		int leftHight = depth(ptr->leftchild);
		int rightHight = depth(ptr->rightchild);
		return (leftHight > rightHight ? leftHight : rightHight) + 1;
	}
	static void rotateWithLeftChild(AVLNode *&ptr)
	{
		AVLNode *newroot = ptr->leftchild;
		AVLNode *childRight = newroot->rightchild;
		if (childRight)
			childRight->parent = ptr;
		ptr->leftchild = childRight;
		ptr->parent = newroot;
		newroot->rightchild = ptr;
		newroot->parent = ptr->parent;
		ptr = newroot;
		//处理平衡因子
		newroot->rightchild->balance = 0;
		newroot->balance = 0;
	}
	static void doubleWithLeftChild(AVLNode *&ptr)
	{
		if (depth(ptr->leftchild->leftchild) == depth(ptr->leftchild->rightchild))
			return;
		rotateWithRightChild(ptr->leftchild);
		rotateWithLeftChild(ptr);

	}	
	static void rotateWithRightChild(AVLNode *&ptr)
	{
		AVLNode *newroot = ptr->rightchild;
		AVLNode *childLeft = newroot->leftchild;
		newroot->parent = ptr->parent;
		if (childLeft)
			childLeft->parent = ptr;
		ptr->rightchild = childLeft;
		ptr->parent = newroot;
		newroot->leftchild = ptr;
		ptr = newroot;
		//处理平衡因子
		newroot->leftchild->balance = 0;
		newroot->balance = 0;
	}
	static void doubleWithRightChild(AVLNode *&ptr)
	{
		if (depth(ptr->rightchild->leftchild) == depth(ptr->rightchild->rightchild))
			return;
		rotateWithLeftChild(ptr->rightchild);
		rotateWithRightChild(ptr);
	}
	static int Insert(AVLNode *&ptr, const _Ty &x, AVLNode *pa)
	{
		int res = 0;
		if (ptr == NULL)
		{
			ptr = _Buynode();
			ptr->key = x;
			ptr->balance = 0;
			ptr->parent = pa;
			ptr->leftchild = ptr->rightchild = NULL;
			res = 1;
		}
		else if (x < ptr->key)
		{
			res = Insert(ptr->leftchild, x, ptr);
			if (res == 2 || res == 0)
				return res;
			switch (ptr->balance)
			{
			case 0: ptr->balance--; break;
			case 1: ptr->balance--; res = 2; break;
			case -1:
				if (x < ptr->leftchild->key)				//左左 旋转一次
					rotateWithLeftChild(ptr);
				else										//左右 旋转两次
					doubleWithLeftChild(ptr);
			res = 2;
				break;
			}
		}
		else if (x > ptr->key)
		{
			res = Insert(ptr->rightchild, x, ptr);
			if (res == 2 || res == 0)
				return res;
			switch (ptr->balance)
			{
			case 0: ptr->balance++; break;
			case -1: ptr->balance++; res = 2; break;
			case 1:
				if (ptr->rightchild->key < x)				//右右 旋转一次
					rotateWithRightChild(ptr);
				else										//右左 旋转两次
					doubleWithRightChild(ptr);				
				res = 2;
				break;
			}
		}
		return res;
	}
	bool Insert(const _Ty &x)
	{
		return Insert(root, x, NULL) > 0;
	}
};

void main()
{
	int ar[] = { 7,5,9,3,6,8,10,2,4,1};
	int n = sizeof(ar) / sizeof(ar[0]);
	AVLTree<int> myt;
	for (int i = 0; i<n; ++i)
	{
		myt.Insert(ar[i]);
	}
}