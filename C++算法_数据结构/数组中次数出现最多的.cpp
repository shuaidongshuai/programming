#include <iostream>
#include <map> 
using namespace std;

//找整数数组中出现次数最多的那个数，如果有多个输出数字最小的 
//1.如果这个数超过一半  有个O(N)的算法
 
//2.用hash表最好，但是2有个问题 （如果自己构造hash函数  需要根据题目要求才能构造合理的函数）
//								（还有如果用了hash函数 你的key就不是从小到大排序的） 

//3.hash表其实可以换成map  这样时间复杂度就变成了NlogN 但是不用考虑key了
void findMaxNum(int *arr, int len){
	map<int, int> hmp;//使用stl默认的hash函数，有点不太合适
	for(int i = 0; i < len; ++i){
		auto it = hmp.find(arr[i]);
		if(it == hmp.end())
			hmp[arr[i]] = 1;
		else
			++hmp[arr[i]];
	}
	int max = 0, max_num; 
	for(auto m : hmp){
		if (max < m.second){
			max_num = m.first;
			max = m.second;
		}
		cout << m.first << " -> " << m.second << endl;
	}
	cout << max_num << endl;
}

int main(){
	int arr[] = {4,5,3,4,3,4,9,10,3};
	findMaxNum(arr, sizeof(arr) / sizeof(arr[0]));
}
