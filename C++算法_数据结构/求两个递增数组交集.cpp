//两个有序递增数组A,B        
//A中有100万个数字，B中有100个数字，求交集 
#include <iostream>
#include <vector>
using namespace std;

void findSame(vector<int> a, vector<int> b, vector<int> &s){
	if(a.empty() || b.empty())
		return;
	s.clear();
	int aSize = a.size();
	int bSize = b.size();
	int i = 0, j = 0;
	while(i < aSize && j < bSize){
		while(b[j] < a[i])
			++j;
		if(b[j] == a[i]){
			s.push_back(a[i]);
			++j;
		}
		++i;
	}
}

int main(){
	int a[] = {1,3,7,9,10};
	int b[] = {5,7,8,9,10};
	vector<int> av(a, a + sizeof(a)/sizeof(a[0]));
	vector<int> bv(b, b + sizeof(b)/sizeof(b[0]));
	vector<int> s;
	findSame(av, bv, s);
	for(auto i : s)
		cout<<i<<" ";
	cout<<endl;
}
