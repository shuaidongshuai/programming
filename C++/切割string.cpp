#include<iostream>
#include<vector>
#include <list>
using namespace std;

int SplitStr(string str, string spl, vector<string> &v){
	if(str.empty())
		return 0;
	v.clear();
	if(spl.empty()){
		v.push_back(str);
		return 1;
	}
	int start = 0, end = 0, strSize = str.size(), splSize = spl.size();
	while(1){
		end = str.find(spl, start);//失败返回-1 
		if(end == -1){
			string endStr = str.substr(start, strSize - start);//最后一个字符串
			if(!endStr.empty())	//防止最后一个字符串为空 
				v.push_back(endStr);
			break;
		} 
		if(end > start)
			v.push_back(str.substr(start, end - start));
		start = end + splSize;
	}
	
	return v.size();
} 
///////////////////////////////////////////////////////////////////////////
void print(string str, vector<string> &v){
	cout<<str<<endl;
	for(auto it : v){
		cout<<it<<",";
	}
	cout<<endl<<"-------------------------"<<endl;
}

int main(){
	vector<string> v;
	string str("123123gdasfdsa123eewfgfd123hgffdr123gfsdcb123123");
	string str2("123fdsa123fdsa");
	string str3("fsdfsdag123");
	string str4("fsdfsdag123fdsa");
	SplitStr(str, "123", v);
	print(str, v);
	SplitStr(str2, "123", v);
	print(str2, v);
	SplitStr(str3, "123", v);
	print(str3, v);
	SplitStr(str4, "123", v);
	print(str4, v);
	SplitStr(str4, "", v);
	print(str4, v); 
} 
