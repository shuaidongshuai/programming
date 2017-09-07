#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*题目：给定一个二维平面上的n个点，找到位于同一直线上的点的最大数目*/
/*
思路：把每一个点和其他的点进行求斜率，就能得到这个点最大能和几个点在同一条直线上 
*/

class Point
{
public:
	int x,y;
	Point(int x = 0,int y = 0):x(x),y(y){}	
};

int getMaxPoint(vector<Point> &v)
{
	int size = v.size();
	if(0 == size) return 0;
	else if(1 == size) return 1;
	
	int res = 0;
	for(int i = 0; i < size; ++i)
	{
		map<double,int> map;//斜率，次数 
		int vcnt = 0; //垂直点
        int dup = 1; //重复点
        int curmax = 0;
		for(int j = i + 1; j < size; ++j)
		{
			if(v[i].x == v[j].x)
			{
				if(v[i].y == v[j].y)
					++dup;
				else
					++vcnt;
				curmax > vcnt ?: curmax = vcnt;
			}
			else
			{
				double k = (double)(v[i].y - v[j].y) / (v[i].x - v[j].x);//注意这里是int / int = int   需要强转 double / int = double 
				curmax > ++map[k] ?: curmax = map[k];
			}
		}
		curmax += dup;
		res > curmax ?: res = curmax;
	}
	return res;
} 

int main()
{
	
}
