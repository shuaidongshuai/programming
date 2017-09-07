#include <iostream> 
#include <vector>
using namespace std;

int main()
{
	int row = 5;
	int col = 6;
	/* 用vector 一句话完成二维数组的建立+初始化*/
	vector<vector<int> > v(row,vector<int>(col,0));//注意dev里面 >> 会造成误解 > >加空格就好 
	
	for(int i = 0;i<row;++i)
	{
		for(int j = 0;j<col;++j)
			cout<<v[i][j]<<" ";
		cout<<endl;
	}
	
}

