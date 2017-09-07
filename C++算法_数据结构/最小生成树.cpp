#include <iostream>
using namespace std;

#define MAX 100
#define MAXCOST 0x7fffffff 

int prim(int graph[][MAX],int n)
{
	int lowcost[MAX];  //MAX 是这个邻近点id   这个数组代表了，当前没有加入到集合中的点，到集合的最短距离 
	int mst[MAX];
	int min,minid,sum = 0;
	for(int i = 2;i<n;i++)
	{
		lowcost[i] = graph[1][i];//第一个点，到邻近点的距离
		mst[i] = 1;
	}
	mst[1]  = 0;
	for(int i = 2; i <= n; i++)
	{
		min = MAXCOST;// 当前点到邻近点的距离 
		minid = 0;	//这个邻近点的id
		
		/*找到最短距离并记录*/
		for(int j = 2; j <= n; j++) 
		{
			if(lowcost[j] < min && lowcost[j] != 0)
			{
				min = lowcost[j];
				minid = j;
			}
		}
		cout << "V" << mst[minid] << "-V" << minid << "=" << min << endl;
		sum += min;//用于计算最小生成树值 
		lowcost[minid] = 0;//当前节点到 自己肯定是距离是0  ********************************************
		
		for(int j = 2; j <= n; j++) 
		{
			if(graph[minid][j] < lowcost[j])
			{
				lowcost[j] = graph[minid][j];
				mst[j] = minid;					//现在集合中 minid -> j 节点是最短的 
			}
		}
	}
	return sum;
}

int main()
{
	int graph[MAX][MAX];
	int i, j, k, m, n;
	int x, y, cost;
	cin >> m >> n;
	//初始化图G  
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= m; j++)
		{
			graph[i][j] = MAXCOST;
		}
	}
	//构建图G  
	for (k = 1; k <= n; k++)
	{
		cin >> i >> j >> cost;
		graph[i][j] = cost;
		graph[j][i] = cost;
	}
	//求解最小生成树  
	cost = prim(graph, m);
	//输出最小权值和  
	cout << "最小权值和=" << cost << endl;
	return 0;
}
/*
MST（Minimum Spanning Tree，最小生成树）问题有两种通用的解法，Prim算法就是其中之一，它是从点的方面考虑构建一颗MST，
大致思想是：设图G顶点集合为U，首先任意选择图G中的一点作为起始点a，将该点加入集合V，再从集合U-V中找到另一点b使得点b到V中任意一点的权值最小，
此时将b点也加入集合V；以此类推，现在的集合V={a，b}，再从集合U-V中找到另一点c使得点c到V中任意一点的权值最小，此时将c点加入集合V，直至所有顶点全部被加入V，
此时就构建出了一颗MST。因为有N个顶点，所以该MST就有N-1条边，每一次向集合V中加入一个点，就意味着找到一条MST的边。

lowcost[i]:表示以i为终点的边的最小权值,当lowcost[i]=0说明以i为终点的边的最小权值=0,也就是表示i点加入了MST
mst[i]:表示对应lowcost[i]的起点，即说明边<mst[i],i>是MST的一条边，当mst[i]=0表示起点i加入MST

///////////////////////////////****************************************
我感觉最难的是理解		mst[2]=3 
看了好久，终于明白是啥意思了，，mst[2]=3  就是  3号节点（集合中的） 到 2号节点(还没加入到集合中) 的最短路径的一个点 

6 10
1 2 6
1 3 1
1 4 5
2 3 5
2 5 3
3 4 5
3 5 6
3 6 4
4 6 2
5 6 6
*/ 
