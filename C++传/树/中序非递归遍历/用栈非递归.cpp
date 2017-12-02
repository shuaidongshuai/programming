#include <iostream>
#include <cstdlib>
#include <stack>
#include "Tree.h"
using namespace std;

//非递归中序遍历
void inOrder(Tree t)
{
	stack<Tree> stackTree;
	Tree p = t;
	if (!t)
	{
		cout << "这是一个空树" << endl;
	}
	//下面的代码比较完美（百度）
	while (t || !stackTree.empty())
	{
		while (t)				//和上面的区别在于，比较的是自己，而不是自己的left孩子
		{
			stackTree.push(t);//只要自己存在，就入栈
			t = t->left;	//然后再遍历左子树
		}
		//现在的t是NULL的
		t = stackTree.top();//首先获取父节点
		stackTree.pop();	//并弹出栈
		printf("%c   ", t->val);//打印这个值
		t = t->right;		//遍历这个节点的右子树，，好处在于就算right是空，下一次循环又是获取栈中的父节点，不为空入栈就是了
	}

	cout << endl << "方法2" << endl;
	while (!stackTree.empty() || p)
	{
		if (p)//不为空就入栈，并指向左子树
		{
			stackTree.push(p);
			p = p->left;
		}
		else//为空就 取出栈顶 元素，并指向右子树
		{
			p = stackTree.top();
			stackTree.pop();
			cout << p->val << "   ";
			p = p->right;
		}
	}
}

//非递归先序遍历
void preOrder(Tree t)
{
	if (t == NULL)
		return;
	stack<Tree> stackTree;
	Tree p = t;

	/*第一种方法容易理解★★★★★建议看这种★★★★★*/
	while (t || !stackTree.empty())
	{
		while (t)
		{
			stackTree.push(t);//只要自己存在，就入栈
			printf("%c   ", t->val);//打印这个值
			t = t->left;	//然后再遍历左子树
		}
		//现在的t是NULL的
		t = stackTree.top();//首先获取父节点
		stackTree.pop();	//并弹出栈
		t = t->right;		//遍历这个节点的右子树，，好处在于就算right是空，下一次循环又是获取栈中的父节点，不为空入栈就是了
	}
	cout << endl << "方法2" << endl;

	//方法2 下面只需要一个循环
	while (!stackTree.empty() || p)
	{
		if (p)//不为空就入栈，并打印
		{
			cout << p->val << "   ";
			stackTree.push(p);
			p = p->left;
		}
		else//为空就 取出栈顶 元素，并遍历这个元素的 右子树
		{
			p = stackTree.top();
			stackTree.pop();
			p = p->right;
		}
	}
}

//非递归后序遍历   下面这方法建议不要看，因为后面又更容易理解的
void postOrder(Tree t)
{
	if (!t)
		return;
	stack<Tree> s;
	//pCur:当前访问节点，pLastVisit:上次访问节点
	Tree pCur, pLastVisit = NULL;
	pCur = t;


	//先把pCur移动到左下位置
	while (pCur)								//这里算是步骤1
	{
		s.push(pCur);
		pCur = pCur->left;
	}
	while (!s.empty())//只要栈不为空那么一定存在第一个根节点，所以为不为空作为判断是否全部遍历的条件
	{
		pCur = s.top();//获取父节点
		s.pop();
		//首先判断是否可以访问右孩子，因为只有不能访问右节点的时候才打印，（后序遍历，左右根的遍历）
		if (!pCur->right || pCur->right == pLastVisit)//当右子树不存在  或者 已经被访问过  那么说明向右访问已经结束，可以打印了
		{
			cout << pCur->val << "   ";
			//修改最近被访问的节点
			pLastVisit = pCur;
		}
		else//如果不能打印  那么右子树一定可以访问
		{
			s.push(pCur);//如果还有右孩子 那么根入栈
			pCur = pCur->right;//访问这个节点的右孩子

			while (pCur)//只要右孩子继续遍历他的左子树   //这里也算是步骤1  除了这一步，整个大循环都算步骤2
			{
				s.push(pCur);
				pCur = pCur->left;
			}
		}
	}
}
/*记住第二种方式，和非递归中序遍历非常像，需要加一个判断，判断当前根节点的右孩子是否为空或者是否被访问*/
void postOrder2(Tree t)
{
	if (t == NULL)
		return;
	stack<Tree> stackTree;
	Tree pLastVisit = NULL;

	while (t || !stackTree.empty())
	{
		while (t)
		{
			stackTree.push(t);
			t = t->left;
		}
		t = stackTree.top();
		stackTree.pop();
		if (!t->right || t->right == pLastVisit)
		{
			printf("%c   ", t->val);
			pLastVisit = t;
			t = NULL;								//************这一步我硬是没想到，必须有
		}
		else
		{
			stackTree.push(t);
			t = t->right;
		}
	}
}

/*
后序遍历是最难的，因为他是最先访问左孩子，然后访问右孩子，最后才访问根（并标记已经访问过了）
1.左孩子的访问最简单直接一直循环到没有左孩子为止
2.然后获取右孩子
访问右孩子的时候，就会多一个步骤：每次访问根的时候需要判断右孩子是否有 和 是否已经被访问（当右子树访问完毕，才能打印根）(没有访问完继续1 2 步骤）
步骤1.就是访问左节点
步骤2.就是访问右节点  不能访问时就打印
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*用不同的方法进行二叉树非递归遍历*/
/*这种方法为了应付面试官问：你能换一种方式进行非递归遍历么？
虽然这种方法很废，但是通用性比较高，实现先后中序遍历，代码形式都是一样的
*/
typedef struct Dong
{
	Node *node;
	int times;//次数
	Dong(Node *n, int i = 0) :node(n), times(i){}
}Dong;
void StkNiceInOrder(Node *node)
{
	Dong *d = new Dong(node, 0);
	stack<Dong*> s;
	s.push(d);
	while (!s.empty())
	{
		d = s.top();
		s.pop();
		if (++(d->times) == 1)
		{
			s.push(d);
			if (d->node->left != NULL)					//times == 1的时候应该入左孩子
				s.push(new Dong(d->node->left));
		}
		else if (d->times == 2)
		{
			cout << d->node->val << "   ";
			s.push(d);
			if (d->node->right != NULL)					//times == 2的时候应该入右孩子
				s.push(new Dong(d->node->right));
		}
	}
	cout << endl;
}
void StkNicePostOrder(Node *node)
{
	Dong *d = new Dong(node, 0);
	stack<Dong*> s;
	s.push(d);
	while (!s.empty())
	{
		d = s.top();
		s.pop();
		if (++(d->times) == 1)
		{
			s.push(d);
			if (d->node->left != NULL)
				s.push(new Dong(d->node->left));
		}
		else if (d->times == 2)
		{
			s.push(d);
			if (d->node->right != NULL)
				s.push(new Dong(d->node->right));
		}
		else
			cout << d->node->val << "   ";
	}
	cout << endl;
}
void StkNicePreOrder(Node *node)
{
	Dong *d = new Dong(node, 0);
	stack<Dong*> s;
	s.push(d);
	while (!s.empty())
	{
		d = s.top();
		s.pop();
		if (++(d->times) == 1)
		{
			cout << d->node->val << "   ";
			s.push(d);
			if (d->node->left != NULL)
				s.push(new Dong(d->node->left));
		}
		else if (d->times == 2)
		{
			s.push(d);
			if (d->node->right != NULL)
				s.push(new Dong(d->node->right));
		}
	}
	cout << endl;
}

int main1()
{
	char a[] = { '1', '2', '3', ' ', ' ', '4', ' ', ' ', '5', '6' };//注意这里要两个空格，因为左右子树都需要NULL
	int i = 0;
	Tree root = NULL;
	//先创建一棵树
	createTree(root, a, i);
	cout << "递归中序遍历" << endl;
	//递归中序遍历
	inOrderY(root);//3   2   4   1   6   5
	cout << endl << endl << "非递归中序遍历" << endl;
	//非递归中序遍历
	inOrder(root);//3   2   4   1   6   5


	cout << endl << endl << "递归先序遍历" << endl;
	//递归先序遍历
	preOrderY(root);
	//非递归先序遍历
	cout << endl << endl << "非递归先序遍历" << endl;
	preOrder(root);


	cout << endl << endl << "递归后序遍历" << endl;
	//递归后序遍历
	postOrderY(root);
	//非递归后序遍历
	cout << endl << endl << "非递归后序遍历" << endl;
	postOrder(root);

	cout << endl << endl << "非递归后序遍历第二种方法" << endl;
	postOrder2(root);

	cout << endl << "---------------换一种思路写非递归-------------------------" << endl;
	cout << "中序：" << endl;
	StkNiceInOrder(root);
	cout << "先序：" << endl;
	StkNicePreOrder(root);
	cout << "后序：" << endl;
	StkNicePostOrder(root);
	cin.get();
	return 0;
}
/*
中序 遍历的几种情况
分析1：什么时候访问根、什么时候访问左子树、什么访问右子树
当左子树为空或者左子树已经访问完毕以后，再访问根
访问完毕根以后，再访问右子树。
分析2：为什么是栈，而不是其他队列。
先走到的后访问、后走到的先访问，显然是栈结构
分析3：结点所有路径情况
步骤1：结点的所有路径情况
如果结点有左子树，该结点入栈；
如果结点没有左子树，访问该结点；
分析3：路径所有情况
如果结点有右子树，重复步骤1；
如果结点没有右子树（结点访问完毕），回退，让栈顶元素出栈，访问栈顶元素，并访问右子树，重复步骤1
如果栈为空，表示遍历结束。
注意：入栈的结点表示，本身没有被访问过，同时右子树也没有被访问过。
分析4：有一个一直往左走入栈的操作

*/