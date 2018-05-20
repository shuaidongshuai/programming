#include <iostream>
#include <vector> 
#include <algorithm>
#include <bitset>
using namespace std;
void printVVI(vector<vector<int>> vv){
	auto vvit = vv.begin();
	while(vvit != vv.end()){
		auto vit = (*vvit).begin();
		while(vit != (*vvit).end()){
			cout << *vit++ << " ";
		}
		vvit++; 
		cout << endl;
	}
}
/* 
找两个数的和为N很容易 (1)先排序，前后指针。O(NlogN) (2)hash 然后 遍历一次 O(N) 缺点：对数有要求，耗内存
找三个数的和(1)先排序，指定一个数，找另外两个数用上面的方法实现。O(N^2)  由于要求不重复所以要对上面算法修改 
找四个数应该也可以，但是时间复杂度就是O(N^3) 数越多复杂度越大 所以这种方法不是很好 ---- 不过也是自己的思路 
 */ 
//start end 是为了二分的时候不去前面查找 目的为了不重复 
vector<vector<int>> twoSum(vector<int>& nums, int start, int end, int target){
    int i = start, j = end;
    vector<vector<int>> res;
    while(i < j){
        if(nums[i] + nums[j] == target){
            vector<int> v;
            v.push_back(nums[i]);
            v.push_back(nums[j]);
            res.push_back(v);
            while(nums[i] == nums[++i]);//由于要求不重复，去掉前面和后面相同的数 
            while(nums[j] == nums[--j]);
        }
        else if(nums[i] + nums[j] < target){
            ++i;
        }
        else{
            --j;
        }
    }
    return res;
}
vector<vector<int>> threeSum(vector<int>& nums) {
	sort(nums.begin(), nums.end());
    int size = nums.size();
    int temp;
    vector<vector<int>> res;
    for(int i = 0; i < size - 2; ++i){
    	if(i - 1 >= 0 && nums[i] == nums[i - 1])//由于不重复，去掉后面相同的数 
    		continue;
        temp = 0 - nums[i];//和为0  同理和为N也可以 
        vector<vector<int>> tempRes = twoSum(nums, i + 1, size - 1, temp);
        int tempSize = tempRes.size();
        for(int j = 0; j < tempSize; ++j){
            tempRes[j].push_back(nums[i]);
            res.push_back(tempRes[j]);
        }
    }
    return res;
}

int main1(){
	vector<int> inV{-4,-2,-2,-2,0,1,2,2,2,3,3,4,4,6,6};
	printVVI(threeSum(inV));
}
/*
寻找和为定值的任意多个数
*/
int res[100], k = 0;
void sumOfKNumber(int *a, int n, int sum){
    if(n <= 0 || sum <= 0)
        return;
    if(k > 0){
        if(sum == a[n-1]){
            for(int i = k-1; i >= 0; --i)
                cout << res[i] << ",";
            cout << a[n-1]  << endl; //特别注意，输出时，该元素还未加入数组
        }
    }
    //考虑是否取第n个数
    res[k++] = a[n-1];
    sumOfKNumber(a, n-1, sum-a[n-1]);
    k--;
    sumOfKNumber(a, n-1, sum);
}
int main(){
    int a[100]{-1,0,1,2,-1,-4}, n = 6, ans = 2;
    sumOfKNumber(a, n, ans);
    return 0;
}
