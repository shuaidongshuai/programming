#include <iostream>
#include <cstring>
using namespace std;

typedef struct dong{
	char value;
	struct dong *left;
	struct dong *right;
}*Node, Dong;

Node buyNode()
{
	Node node = new Dong;
	node->value = -1;
	node->left = NULL;
	node->right = NULL;
	return node;
}
#if 0
Node create_tree_byPI2(char *&sp, char *si, int n)
{
	if (sp == NULL || si == NULL || n <= 0)
	{
		--sp;						//这里必加上，因为如果不能遍历了，说明线序遍历还得用这个sp，但是上一个递归已经++了，所以这里需要--
		return NULL;
	}
	int i = 0;
	for (; i < n; i++)
	{
		if (*sp == *(si + i))
			break;
	}
	Node node = buyNode();
	node->value = *sp;
	node->left = create_tree_byPI(++sp, si, i);
	node->right = create_tree_byPI(++sp, si + i + 1, n - i - 1);
	return node;
}
#endif

/*下面这个比上面那个要好一点，不容易出bug  上面bug调试了好久，就是因为引用导致的，不过上面是自己想出来的容易理解*/
Node create_tree_byPI(char *sp, char *si, int n)
{
	if (sp == NULL || si == NULL || n <= 0)
	{
		return NULL;
	}
	int i = 0;
	for (; i < n; i++)
	{
		if (*sp == *(si + i))
			break;
	}
	Node node = buyNode();
	node->value = *sp;
	node->left = create_tree_byPI(sp + 1, si, i);
	node->right = create_tree_byPI(sp + i + 1, si + i + 1, n - i - 1); //这里 sp + i + 1 需要自己理解一下
	return node;
}
/*根据中序 后序 建树 和上面差不多，只是在最后给参数的时候注意是 i + 1  还是 i */
Node create_tree_byIL(char *si, char *sl, int n)
{
	if (sl == NULL || si == NULL || n <= 0)
	{
		return NULL;
	}
	int i = 0;
	for (; i < n; i++)
	{
		if (sl[n - 1] == si[i])
			break;
	}
	Node node = buyNode();
	node->value = sl[n - 1];
	node->left = create_tree_byIL(si, sl, i);
	node->right = create_tree_byIL(si + i + 1, sl + i, n - i - 1);
	return node;
}

/*中序遍历*/
void print(Node root)
{
	if (root == NULL)
		return;
	print(root->left);
	cout << root->value << "\t";
	print(root->right);
}
/*后序遍历*/
void print2(Node root)
{
	if (NULL == root)
		return;	
	print2(root->left);
	print2(root->right);
	cout << root->value << "\t";
}

int main()
{
	/*由于我们从头到尾没有改变字符串，所以可以这样直接指向，但是要注意：如果我们要改变需要 new*/
	char *sp = "ABDEFGC";//先序
	char *si = "DBFEGAC";//中序
	char *sl = "DFGEBCA";//后序
	Node root = create_tree_byPI(sp, si, strlen(si));
	print(root);/*中序遍历*/
	cout << endl << "------------------------------------------------" << endl;
	Node root2 = create_tree_byIL(si, sl, strlen(si));
	print2(root2);

	getchar();
}
