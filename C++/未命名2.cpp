#include <iostream>
#include <vector> 
using namespace std;

class A{
public:
	A(){
		cout <<"¹¹Ôì"<<endl; 
	}	
	~A(){
		cout << "~A()"<<endl;
	}
};
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
int main(){
	vector<vector<int>> res;
	vector<int> v;
    v.push_back(1);
    v.push_back(2);
    res.push_back(v);
    printVVI(res); 
	cout<<"---"<<endl;
}
