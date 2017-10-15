#include <iostream>
#include <cstdlib>
using namespace std;
/*
	atoi()会扫描参数nptr字符串，跳过前面的空格字符，
	直到遇上数字或正负号才开始做转换，而再遇到非数字或字符串时（'\0'）才结束转化，
	并将结果返回（返回转换后的整型数）
	如果 nptr不能转换成 int 或者 nptr为空字符串，那么将返回 0
*/
int AtoiDong(const char *str){
	if(!str)
		return 0;
	while(*str == ' ')
		++str;
	int head = 1, sum = 0;
	if(*str == '-'){
		head = -1;
		++str;
	}
	else if(*str == '+'){
		++str;
	}

	while(*str >= '0' && *str <= '9'){
		sum = 10 * sum + *str - '0';
		++str;
	}
	return head * sum;
}

int main(){
	char *str = "    -43432.435";
	cout<<atoi(str)<<endl;
	cout<<AtoiDong(str)<<endl;
}
