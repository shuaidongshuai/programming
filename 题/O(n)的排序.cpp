#include <iostream>
using namespace std;
/* 对几万员工的年龄排序，时间效率O(n) 辅助内存不超过O(n)*/

void SortAges(int *age,int len)
{
	int oldestAge = 100;//设最老的，能活100岁
	int timesOfAge[oldestAge];
	for(int i = 0;i<oldestAge;i++)
		timesOfAge[i] = 0;
	for(int i = 0;i<len;i++)
		timesOfAge[age[i]]++;
	
	int index = 0; 
	for(int i = 0 ;i<oldestAge;i++)
		for(int j = 0;j<timesOfAge[i];j++)
			age[index++] = i;
} 

int main()
{
	int age[] = {18,18,19,20,50,40,30,45,34,46,34,62,43,58,69,23,45,65,55,65,67,34,34,56,43,58,69,23,45,65,55,65,67,34,34,56};//假设是所有员工的年龄 
	int n = sizeof(age) / sizeof(age[0]);
	SortAges(age,n);
	for(int i = 0;i<n;i++)
		cout<<age[i]<<" ";
}
