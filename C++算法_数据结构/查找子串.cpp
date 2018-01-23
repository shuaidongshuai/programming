#include <iostream>
#include <cstring>
using namespace std;
//bfËã·¨ 
char *FindSubstr(char *str, char *substr){
	if(!str || !substr)
		return NULL;
	int len1 = strlen(str);
	int len2 = strlen(substr);
	int j;
	for(int i = 0; i < len1; ++i){
		j = 0;
		for(int k = i; k < len1; ++k){
			if(str[k] == substr[j]){
				++j;
				if(j == len2)
					return str + i;
			}
			else{
				break;
			}
		}
	}
	return NULL;
}
void test(){
	char *str = "hello dong nice to meet you";
	char *sub = "nice";
	char *res = FindSubstr(str, sub);
	cout<<res<<endl;
	
	sub = "you";
	res = FindSubstr(str, sub);
	cout<<res<<endl;
	
	sub = "domg";
	res = FindSubstr(str, sub);
	cout<<res<<endl;
}

int main(){	
	test();
}

