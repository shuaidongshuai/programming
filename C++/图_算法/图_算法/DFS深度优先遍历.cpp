#include <iostream>
using namespace std;

#define ElemType char
#define EdgeType int
#define MAXNUM	 100
int visited[MAXNUM];//访问标识数组 

class Graph
{
public:
	ElemType value[MAXNUM];
	EdgeType edges[MAXNUM][MAXNUM];
	int n;//节点个数
	int e;//边数
};

void createMGraph(Graph *G);

void DFS(Graph *G, int ivex)
{
	if (!G)
		return;
	visited[ivex] = 1;
	cout << G->value[ivex] << "\t";
	for (int i = 0; i < G->n; i++)
	{
		if (!visited[i] && G->edges[ivex][i])
		{
			visited[i] = 1;//1表示已经被访问
			DFS(G, i);
			return;
		}
	}
	/*如果当前节点无路可走，but还有点没有遍历到*/
	int j = 0;
	for (; j < G->n; j++)
	{
		if (!visited[j])
		{
			visited[j] = 1;//1表示已经被访问
			DFS(G, j);
			return;
		}
	}
}

int main3()
{
	Graph* G = new Graph;
	createMGraph(G);
	DFS(G, 0);
	system("pause");
	return 0;
}
