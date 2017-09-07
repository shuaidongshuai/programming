#include "common.h"

using namespace std;

class WRR
{
	list<int> weight_list;
	int weight_arr[5];
	int current;
public:
	WRR()
	{
		current = 0;
		int num;
		//根据用户情况自己设置，我设置的是双数服务器权大
		for(int i = 0;i<5;i++)
		{
			if(i % 2 == 1)
				num = 2;
			else
				num = 1;
			weight_arr[i] = num;
			weight_list.push_back(num);
		}
	}
	int get()
	{
		if((*weight_list.begin())-- == 0)
		{
			weight_list.erase(weight_list.begin());//删除头元素
			weight_list.push_back(weight_arr[current]);//把这个头元素原始值加入到list尾
			(*weight_list.begin())--;//因为这次用的就是它所以得减一次
			current = (current + 1) % 5;
		}
		return current;
	}
};