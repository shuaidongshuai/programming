/*
问题描述
　　学霸抢走了大家的作业，班长为了帮同学们找回作业，决定去找学霸决斗。但学霸为了不要别人打扰，住在一个城堡里，城堡外面是一个二维的格子迷宫，要进城堡必须得先通过迷宫。因为班长还有妹子要陪，磨刀不误砍柴功，他为了节约时间，从线人那里搞到了迷宫的地图，准备提前计算最短的路线。可是他现在正向妹子解释这件事情，于是就委托你帮他找一条最短的路线。
输入格式
　　第一行两个整数n， m，为迷宫的长宽。
　　接下来n行，每行m个数，数之间没有间隔，为0或1中的一个。0表示这个格子可以通过，1表示不可以。假设你现在已经在迷宫坐标(1,1)的地方，即左上角，迷宫的出口在(n,m)。每次移动时只能向上下左右4个方向移动到另外一个可以通过的格子里，每次移动算一步。数据保证(1,1)，(n,m)可以通过。
输出格式
　　第一行一个数为需要的最少步数K。
　　第二行K个字符，每个字符∈{U,D,L,R},分别表示上下左右。如果有多条长度相同的最短路径，选择在此表示方法下字典序最小的一个。
样例输入
Input Sample 1:
3 3
001
100
110

Input Sample 2:
3 3
000
000
000
样例输出
Output Sample 1:
4
RDRD

Output Sample 2:
4
DDRR
*/ 
#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>

using namespace std;

struct p{
	int x,y;
	int cou;
	string str;
	p(int x,int y,int cou,string str):x(x),y(y),cou(cou),str(str){}
};

char map[510][510];
bool mapp[510][510];
queue<p>Q;
int n,m;
//按照D,L,R,U的顺序
int dir[4][2] = {{1,0},{0,-1},{0,1},{-1,0}};//要保证D在R前面，因为（ 2.既然都能走到这，何不取第一次走的路径 ）  题目要求要字典序最小的 

bool check(int x,int y)//检查当前要走的点是否满足条件 
{
	if(x<0 || x>=n || y<0 || y>=m || mapp[x][y])//因为将要走的坐标有  负号   所以得有 x 和 y 可能小于 0  
	return false;
	return true;
 } 

void bfs()
{
	p tp = p(0,0,0,"");
	while(!Q.empty())
	Q.pop(); 
	//上面三步是对队列的初始化 
	Q.push(tp);
	mapp[0][0] = 1;
	while(!Q.empty())
	{
		p np = Q.front();//每次取队列的第一个 结构体  进行下面的判断 
		Q.pop();		//取完队列的第一个 结构体  就马上在队列中 删除这个 结构体 
		
		for(int i=0;i<4;i++)
		{
			int cx = dir[i][0],cy = dir[i][1];//cx代表将要向上走还是下走，cy代表将要向左走还是右走 
			int nx = np.x + cx,ny = np.y + cy;//nx代表当前位置的横坐标，ny代表当前位置的纵坐标 
			string ts = "";
			if(check(nx,ny))
			{
				//检查通过   判断 这次走的方向 
				if(cx == 1)
				ts = "D";
				if(cx == -1)
				ts = "U";
				if(cy == 1)
				ts = "R";
				if(cy == -1)
				ts = "L"; 
				
				if(nx == n-1 && ny == m-1)//n-1 m-1 那是因为我们坐标是从(0,0)开始的，题目要求是(1,1) 
				{
					cout<<np.cou+1<<endl;
					cout<<np.str+ts<<endl;
					return ;
				}
				Q.push(p(nx,ny,np.cou+1,np.str+ts));
				mapp[nx][ny] = 1;// 每走过一次 不允许再走第二次，因为 1.走第二次，肯定不是最佳路径 2.既然都能走到这，何不取第一次走的路径 
			}
		}
			
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		scanf("%s", map[i]);
		
		for(int j=0;j<m;j++)//把字符串转化为 bool 类型 
		if(map[i][j]=='1')
		mapp[i][j] = true;//true 代表此处不可走 
	}

	bfs();
	return 0;
}
