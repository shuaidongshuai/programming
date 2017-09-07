#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct NODE{
	int val;
	struct NODE *left;
	struct NODE *right;
	NODE(int val) :val(val), left(NULL), right(NULL){}
}Node, *Tree;
void create(Tree &p, int val)
{
	if (p == NULL)
		p = new Node(val);

	else
	{
		if (val < p->val)
			create(p->left, val);

		if (val > p->val)
			create(p->right, val);
	}
}
/*思想很简单，就是无论树有多大，我就把他当做一个root下的一个Left和Right这样的三个节点（或许只有两个节点或许就只有root一个节点）
编程思路：1.挨个挨个判断一个节点下面是否有孩子，如果有孩子，那么就+1（但是这样就不是高度了，是节点个数了） 最后再+1（root）
		  2.把上面进行优化，我只判断左子树的孩子，只遍历做孩子，直到没有孩子为止（这样做呢会导致如果右边高的情况被忽视掉）
		  3.再次对上面优化，每次遍历左右孩子的时候加上一个判断，判断左孩子是否大于右孩子个数（实质就是
			有一个孩子就+1没有孩子就返回0，在返回高度的时候加上一个条件 返回的是左右孩子中最高的一个，然后就递归）
*/
int getDepth(Tree root)
{
	int depthVal, depthLeft, depthRight;

	if (!root)
		return 0;

	//求左子树高度				（把这棵树想成一个root 一个left 一个right 一共三个节点，或者 没有right 只有两个节点，这样容易明白一点） 
	depthLeft = getDepth(root->left);
	//求右子树高度 
	depthRight = getDepth(root->right);
	depthVal = (depthLeft>depthRight ? depthLeft : depthRight) + 1;//每一次递归起码要+1，除非到底了
	return depthVal;
}
/*第二种思路  简单*/
int max(int a, int b)
{
	return a > b ? a : b;
}
int getDepth2(Tree root)
{
	if (!root) return 0;
	return max(getDepth2(root->left), getDepth2(root->right)) + 1;//返回左子树，和右子树最高的，然后 + 1（根）
}
int main1()
{
	int a[20];
	Tree root = NULL;
	//先创建一棵树 
	for (int i = 0; i<10; i++){
		a[i] = rand() % 100;
		printf("%-5d", a[i]);
	}
	for (int i = 0; i<10; i++)
		create(root, a[i]);

	cout << endl;
	//求出树的深度 
	cout << "树高度" << getDepth(root) << endl;

	cout << "树高度" << getDepth2(root) << endl;

	cin.get();
	return 0;
}
