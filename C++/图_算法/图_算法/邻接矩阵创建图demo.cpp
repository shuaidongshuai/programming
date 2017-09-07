#include <iostream>
using namespace std;

#define MaxVertexNum 100 /*最大顶点数设为100*/
typedef char VertexType; /*顶点类型设为字符型*/
typedef int EdgeType; /*边的权值设为整型*/

typedef struct {
	VertexType vexs[MaxVertexNum]; /*顶点表*/
	EdgeType edges[MaxVertexNum][MaxVertexNum]; /*邻接矩阵，即边表*/
	int n, e; /*顶点数和边数*/
}Mgragh; /*Maragh 是以邻接矩阵存储的图类型*/

//建立一个图的邻接矩阵存储的算法如下：
void CreateMGraph(Mgragh *G)
{
	int i, j, k, w, value;
	char ch;
	printf("请输入顶点数和边数\n");
	cin >> G->n >> G->e;/*输入顶点数和边数*/
	printf("请输入顶点信息(输入格式为:顶点号):\n");
	for (i = 0; i<G->n; i++)
		cin >> G->vexs[i]; /*输入顶点信息，建立顶点表*/

	/*初始化邻接矩阵*/
	for (i = 0; i<G->n; i++)
		for (j = 0; j<G->n; j++)
			G->edges[i][j] = 0;

	printf("请输入每条边对应的两个顶点的序号(输入格式为:i j):\n");
	for (k = 0; k < 2 * G->e; k++)
	{
		cin >> i >> j >> value;
		G->edges[i][j] = value;
	}
}
void print(Mgragh *G)
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
int main1()
{
	Mgragh* G = new Mgragh;
	CreateMGraph(G);
	print(G);
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