//都不用辅助空间，用辅助空间为low了
#include <iostream>
using namespace std;

 //这个是去掉全部空格
void RemoveBlankSpace(char *str){
	if(!str)
		return;
	char *head, *tail;
	head = tail = str;
	while(1){
		 //去掉前面空格
		while(*head == ' ')
			++head;
		//判断是否到结尾了
		if(*head == '\0')
			break;
		*tail++ = *head++;
	}
	for(;tail < head; ++tail)
		*tail = 0;
}
void test1(){
	char str[] = "   hel l o     do n g   ";
	RemoveBlankSpace(str);
	cout<<str<<endl;
}
//这个是去掉多余的空格  如(  hello    dong   ) -> (hello dong)
void RemoveBlankSpace2(char *str){
	if(!str)
		return;
	char *head, *tail;
	head = tail = str;
	while(1){
		//去掉前面空格
		while(*head == ' ')
			++head;
		if(*head == '\0')//结尾处为空格
			break;
		while(*head != '\0' && *head != ' ')//结尾处为单词
			*tail++ = *head++;
		*tail++ = ' ';//每个单词之间加一个空格
	}
	*tail = 0;//把最后一个空格变成结束符
}
void test2(){
	char str[] = "   hello   chen   ming   dong";
	RemoveBlankSpace2(str);
	cout<<str<<endl;
}
int main(){
	test2(); 
}
