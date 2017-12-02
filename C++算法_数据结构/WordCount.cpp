#include <iostream>
#include <map>
#include <string> 
using namespace std;

void WorldCount(string str){
	if (str.empty())
		return;
	auto start = str.begin();
	auto end = start;
	map<string, int> m;
	while (end != str.end()){
		//注意：内部也要判断是否溢出  和 快排一样
		while (start != str.end() && (*start == ' ' || *start == '\n' || *start == '\t'))
			++start;
		end = start; 
		while (end != str.end() && *end != ' ' && *end != '\n' && *end != '\t')
			++end;
		if (start == str.end())//为什么是start 不是 end ？？ 因为最后一个字符串打印不出来 
			break;
		string s(start, end);
		if (m.find(s) == m.end())
			m[s] = 1;
		else
			++m[s];
		start = end;
	}
	for (auto it = m.begin(); it != m.end(); ++it)
		cout << it->first << ":" << it->second << endl;
}

int main() {
	string str("  chen ming dong \
hello dong nice to meet you!! \
chen ming dong  ");
	WorldCount(str);
}
