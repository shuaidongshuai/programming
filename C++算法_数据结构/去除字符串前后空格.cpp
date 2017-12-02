#include <iostream> 
#include <cstring>
using namespace std;
//一个函数实现给定字符串，去除前面和后面的空格，比如“ ab cd ”
//最后得到的结果是"ab cd"，不能改变字符串的地址 

void RemoveFrontRearBlank(char *&str){
	if(!str)
		return;
	char *start = str;
	char *end = str + strlen(str) - 1;
	while(' ' == *start)
		++start;
	if(end - start < 0){
		*str = '\0';
		return;
	}
	while(' ' == *end)
		--end;
	char *front = str;
	while(end >= start)
		*front++ = *start++;
	*front = '\0';//这里也容易疏忽 
}
/* 测试用例也超级重要 */
void TestRemoveFrontRearBlank(){
	const int size = 8;
	char **str = new char*[size];
	for(int i = 1; i < size; ++i)
		str[i] = new char[100];
	str[0] = NULL;
	strcpy(str[1], "");
	strcpy(str[2], "a");
	strcpy(str[3], " a");
	strcpy(str[4], "a ");
	strcpy(str[5], " a ");
	strcpy(str[6], "  a  b  c  ");
	strcpy(str[7], "      ");//这个测试用例很重要，和面试官讲清楚全是空格的应该怎么处理？应该处理成 \0
	for(int i = 1; i < size; ++i){
		cout<<str[i]<<endl;
		cout<<"len = "<<strlen(str[i])<<endl;
		RemoveFrontRearBlank(str[i]);
		cout<<str[i]<<endl;
		cout<<"len = "<<strlen(str[i])<<endl;
		delete[] str[i];//如果new了一定要自己delete 
		cout<<"---------------------"<<endl;
	}
	delete[] str;
}
int main(){
	TestRemoveFrontRearBlank();
}
