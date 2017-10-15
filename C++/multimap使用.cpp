#include <iostream>
#include <map>
using namespace std;

int main(){
	multimap<string, int> scoreMap;
	scoreMap.insert(make_pair("cmd",65));
	scoreMap.insert(make_pair("cmd",86));
	scoreMap.insert(make_pair("cmd",98));
	scoreMap.insert(make_pair("dong",43));
	scoreMap.insert(make_pair("dong",56));
	 //遍历
     for(multimap<string, int>::iterator it = scoreMap.begin(); it != scoreMap.end(); it++){
             cout<< it->first<<":"<<it->second<<endl;
     }
     //计数
     int num = scoreMap.count("cmd");
	 cout << num <<endl;
	 //找指定键的所有值
     multimap<string, int>::iterator it2 = scoreMap.find("cmd");
     while(it2 != scoreMap.end() && num--){
        cout << it2->first<<":"<< it2->second<<endl;
        it2++;
     }
}
