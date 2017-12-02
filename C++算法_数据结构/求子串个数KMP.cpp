//s1:abc s2:ababcdd 求s2 里面有几个s1 并返回下标
#include <iostream>
#include <vector>
#include <string> 
using namespace std;

void FindSubStr(string str1, string str2, vector<int> v){
	if(str1.empty() || str2.empty())
		return;
	v.clear();
	int size1 = str1.size();
	int size2 = str2.size();
	for(int i = 0; i < size1; ++i){
		int res = true;
		for(int j = 0; j < size2; ++j){
			if(str1[i] == str1[j])
				++i;
			else
				res = false;
		}
	}
}

int main(){
	
}
