#include<iostream>
//用记录结果再利用的动态规划的方法，上面用递归的方法有很多重复的计算，效率不高。我们可以记录每一次的计算结果，下次要用时再直接去取，以提高效率 
using namespace std;
int N,M,weight[201],value[201],record[200][200];
void init()
{
	for(int i = 0; i < N; i ++)
	{
		for(int j = 0; j < M; j ++) 
		{
			record[i][j] = -1;
		}
	}
}

int solve(int i, int residue)
{
	if(-1 != record[i][residue])
		return record[i][residue];
	int result = 0;
	if(i >= N)
		return result;
	if(weight[i] > residue)
	{
		record[i + 1][residue] = solve(i+1, residue);
	}
	else 
	{
		return result = max(solve(i+1, residue), solve(i+1, residue-weight[i]) + value[i]);
	}
//	record[i + 1][residue] = result;
}

int main() {
	int i;
	scanf("%d%d",&N,&M);
	for(i=0;i<N;i++)
	scanf("%d%d",&weight[i],&value[i]);
	init();
	int result = solve(0, M);
	cout << result << endl;
	return 0;
}
