#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct NODE{
	int val;
	struct NODE *left;
	struct NODE *right;
	NODE(int val):val(val),left(NULL),right(NULL){}		
}Node,*Tree;
void create(Tree &p,int val)
{
	if(p==NULL)
	p = new Node(val);
	
	else
	{
		if(val < p->val)
		create(p->left,val);
		
		if(val > p->val)
		create(p->right,val);
	}
 } 

int getDepth(Tree root)
{
	int depthVal = 0,depthLeft = 0,depthRight = 0;
	if(!root)
		return 0;
	 
	//求左子树高度								（把这棵树想成一个root 一个left 一个right 一共三个节点，或者 没有right 只有两个节点，这样容易明白一点） 
	depthLeft = getDepth(root->left);
	//求右子树高度
	depthRight = getDepth(root->right);
	depthVal = (depthLeft>depthRight?depthLeft:depthRight) + 1;//高度要算上root这个根
	return depthVal;
}

int main()
{
	int a[20];
 	Tree root = NULL;
 	//先创建一棵树 
 	for(int i=0;i<10;i++){
 	 	a[i] = rand()%100;
		printf("%-5d",a[i]);	
	 }
	for(int i=0;i<10;i++)
 	create(root,a[i]);
	
	//求出树的深度 
	cout<<"树高度"<<getDepth(root)<<endl;
}
