#include <iostream>
using namespace std;
#define MAX 100000

typedef struct {
	int parent;
	int lchild;
	int rchild;
	int weight;
}HuffmanNode;

//创建haffman树
void  huffmanTree(HuffmanNode Node[], int n)
{
	int m1, m2;//两个最小权值点
	int x1, x2;//计算最小权值点时，记录该节点在数组中的序号 
	//初始化整个树
	for (int i = 0; i< 2 * n - 1; i++)
	{
		Node[i].parent = -1;
		Node[i].lchild = -1;
		Node[i].rchild = -1;
		Node[i].weight = 0;//权值	
	}
	//输入n个叶子节点的权值
	for (int i = 0; i<n; i++)
	{
		printf("Please input weight of leaf node %d:\n", i);
		cin >> Node[i].weight;
	}
	//构建树
	for (int i = 0; i < n - 1; i++)//两个节点变成一个节点，最后要剩余一个节点，所以是 n - 1
	{
		m1 = m2 = MAX;//给最小权值初始化一个很大的数
		x1 = x2 = 0;
		for (int j = 0; j<n + i; j++)
		{
			if (Node[j].weight < m1 && Node[j].parent == -1)//出现了最小权值的情况
			{
				m2 = m1;
				m1 = Node[j].weight;
				x2 = x1;
				x1 = j;//记录当前最小权值的Node 在数组中的序号
			}
			else if (Node[j].weight < m2 && Node[j].parent == -1)//出现第二小权值的情况
			{
				m2 = Node[j].weight;
				x2 = j;
			}
		}
		//已经找到两个最小权值，现在构建新的Node（最小两个权值Node的父类）
		Node[n + i].weight = Node[x1].weight + Node[x2].weight;
		Node[n + i].lchild = x1;
		Node[n + i].rchild = x2;
		//改变子节点的parent 为当前创建的节点
		Node[x1].parent = n + i;
		Node[x2].parent = n + i;

		//下面都是测试代码
		cout << "第" << i + 1 << "次合并" << "\t左子树：" << Node[x1].weight << "\t右子树：" << Node[x2].weight << "\t父节点："<< Node[n + i].weight << endl;
	}

}
int main()
{
	int n;
	cout << "要创建几个节点" << endl;
	cin >> n;
	HuffmanNode* Node = new HuffmanNode[2 * n - 1];
	huffmanTree(Node, n);
}
/*
5
18
4
9
8
6
*/
