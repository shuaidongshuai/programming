#include<stdio.h>
int main()
{
	/*输入数据的第一行是 m n 两个整数（3 < m, n < 100），表示正方形格子的行数和列数。
　　接下来是 m 行数据。
　　每行数据为 n 个被空格分开的数字。0 表示白格，1 表示黑格。

　　接下来是一行数据：x y s k, 其中x y为整数，表示蚂蚁所在行号和列号（行号从上到下增长，列号从左到右增长，都是从0开始编号）。s 是一个大写字母，表示蚂蚁头的朝向，我们约定：上下左右分别用：UDLR表示。k 表示蚂蚁走的步数。
输出格式
　　输出数据为两个空格分开的整数 p q, 分别表示蚂蚁在k步后，所处格子的行号和列号。
样例输入
5 6
0 0 0 0 0 0
0 0 0 0 0 0
0 0 1 0 0 0	
0 0 0 0 0 0
0 0 0 0 0 0
2 3 L 5*/
	int i,j,m,n,a[101][101];
	scanf("%d%d",&m,&n);
	for(i=0;i<m;i++)
	for(j=0;j<n;j++)
	scanf("%d",&a[i][j]);
	int x,y,k;
	char s;
	scanf("%d%d",&x,&y);
	getchar();
	scanf("%c%d",&s,&k);
	while(k>0)
	{
		if(a[x][y]==0)
	{
		a[x][y]=1;
		if(s=='L')
		{
		x++;
		s='D';	
		}
		else if(s=='R')
		{
		x--;
		s='U';	
		}
		else if(s=='U')
		{
		y--;
		s='L';
		}
		else if(s=='D')
		{
		y++;
		s='R';	
		}
	}
	else
	{
		a[x][y]=0;
		if(s=='L')
		{
		x--;
		s='U';	
		}
		else if(s=='R')
		{
		x++;
		s='D';	
		}
		else if(s=='U')
		{
		y++;
		s='R';
		}
		else if(s=='D')
		{
		y--;
		s='L';
	}
	}
	k--;
	}
	printf("%d %d",x,y);
	return 0;
 } 
