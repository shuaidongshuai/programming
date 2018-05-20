#include <iostream>
#include <string>
using namespace std;
/* ²»ÓÃ¸¨Öú¿Õ¼ä */ 
void PutBigCharBack(string &str){
	if(str.empty())
		return;
	int size = str.size();
	int pre = 0, next = 0;
	while(next < size && str[next] >= 'a' && str[next] <= 'z')
			next++;
	pre = next;
	while(next < size){			
		while(next < size && str[next] >='A' && str[next] <= 'Z')
			next++;
		if(next >= size)
			break;
		char temp = str[next];
		for(int i = next; i > pre; --i){
			str[i] = str[i - 1];
		}
		str[pre++] = temp;
	}
}
int main(){
	string str; 
	while(cin >> str){
		PutBigCharBack(str);
		cout << str << endl;
	}
} 
