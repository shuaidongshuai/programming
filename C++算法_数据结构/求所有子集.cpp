#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/* 递归 */
void GetSubSets(vector<int> &nums, int idx, vector<int> &temp, vector<vector<int> > &subs){
	subs.push_back(temp);
	int size = nums.size();
	for(int i = idx; i < size; ++i){
		temp.push_back(nums[i]);
		GetSubSets(nums, i + 1, temp, subs);
		temp.pop_back();
	}
}
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int> > subs;
    vector<int> temp;//用来保存上一次的值
	GetSubSets(nums, 0, temp, subs);
	return subs; 
}
/* 非递归两种：1.三个for循环-动态规划  2.利用位运算 */
/*
[], [],  [],  [],     [],  [],     [],     []
[], [1], [],  [1],    [],  [1],    [],     [1]
[], [1], [2], [1, 2], [],  [1],    [2],    [1, 2]
[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]
0 	1 	 10	  11 	  100  101 	   110 	   111
1出现的位置：1 11 101 111 	//都是最后一位为1
2			 10 11 110 111	//都是倒数第二位为1
3			 100 101 110 111
*/ 
/* leetcode */ 
vector<vector<int>> subsets2(vector<int>& nums) {
    int num_subset = pow(2, nums.size()); //子集个数 
    vector<vector<int> > res(num_subset, vector<int>());
    for (int i = 0; i < nums.size(); i++)
        for (int j = 0; j < num_subset; j++)
            if ((j >> i) & 1)
                res[j].push_back(nums[i]);
    return res;  
}
/*
总结：
假设nums = { 1, 2, 3, ... , N }
当N = 0时： subs(0) = {{}};
当N = 1时： subs(1) = { {}, {1} };//subs(1) = subs(0) + subs(0) * 1
当N = 2时： subs(2) = { {}, {1}, {2}, {1, 2} };//subs(1) = subs(1) + subs(1) * 1
f(n) = f(n - 1) + f(n - 1) * n;//f()是一个集合 
*/
/* 自己总结后的写法 -- 容易理解 -- 不用去找位的规律 */
vector<vector<int>> subsets3(vector<int>& nums) {
    vector<vector<int> > res(1, vector<int>());
    for (int i = 0; i < nums.size(); i++){
		 int curSize = res.size();
		 for(int j = 0; j < curSize; ++j){
		 	res.push_back(res[j]);
		 	res[curSize + j].push_back(nums[i]);
		 }
	}
    return res;  
}
//////////////////////////Test/////////////////////////////////
void subsetsTest(){
	vector<int> v;
	v.reserve(3);
	for(int i = 0; i < 3; ++i){
		v.push_back(i + 1);
		cout<<v[i]<<" ";
	}
	cout<<endl;
	vector<vector<int>> subs = subsets(v);
	for(auto sub : subs){
		for(auto s : sub){
			cout<<s<<" ";
		}
		cout<<endl;
	}
}

int main(){
	subsetsTest();
} 
/* 题目： 
https://leetcode.com/problems/subsets/description/
Given a set of distinct integers, nums, return all possible subsets (the power set).
Note: The solution set must not contain duplicate subsets.
For example,
If nums = [1,2,3], a solution is:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/ 
