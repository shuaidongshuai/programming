#include <iostream>
using namespace std;

#define ElemType char
#define EdgeType int
#define MAXNUM	 100
class Graph
{
public:
	ElemType value[MAXNUM];
	EdgeType edges[MAXNUM][MAXNUM];
	int n;//节点个数
	int e;//边数
};

/*无向图存储*/
void createMGraph(Graph *G)
{
	int n, e, value, x, y;
	char ch;
	cout << "请输入 节点个数 边数" << endl;
	cin >> n >> e;
	G->n = n;
	G->e = e;

	/*初始化图de 边 如果不可达或相同点表示成0*/
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			G->edges[i][j] = 0;

	cout << "请输入定点表" << endl;
	/*建立顶点表*/
	for (int i = 0; i < n; i++)
	{
		cin >> ch;
		G->value[i] = ch;
	}
	/*建立邻接矩阵*/
	for (int i = 0; i < 2 * e; i++)
	{
		cin >> x >> y >> value;
		G->edges[x][y] = value;
	}
}
/*无向图还能优化（只需要存储邻接矩阵的上三角或者下三角就行了）但是需要输入者有序的输入才行*/
/*有向图和无向图一样，只是输入的边数变成了一半*/
void MyPrint(Graph *G)
{
	int n = G->n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << G->edges[i][j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	Graph* G = new Graph;
	createMGraph(G);
	MyPrint(G);
	system("pause");
	return 0;
}
/*
5 7
A B C D E
0 1 9
0 2 6
0 3 3
1 0 9
1 2 4
1 3 5
2 0 6
2 1 4
2 4 7
3 1 5
3 0 3
3 4 8
4 3 8
4 2 7
*/