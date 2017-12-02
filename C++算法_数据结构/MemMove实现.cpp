#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
/*
内存重叠问题:
要做的就是，src的内容在不能在copy之前被改变 

源码其实是先判断是否存在交叉，如果没有那么调用memcpy，如果有再执行类似下面的代码
*/ 
void *MemMove(void *dst, void *src, int n){
	if(!dst || !src || n <= 0)
		return dst;
	char *dst_ = (char *)dst;
	char *src_ = (char *)src;
	if(dst_ > src_){//src在前，需要从后往前copy 
		while(--n > 0)
			*(dst_ + n) = *(src_ + n);
	}
	else{//从前往后copy 
		int idx = 0;
		while(idx < n){
			*(dst_ + idx) = *(src_ + idx);
			++idx;
		}
	}
	return dst;
}
void test(){
	char s[] = "1234567890";
	char* p1 = s;
	char* p2 = s+2;
	MemMove(p2, p1, 5);
	cout<<p1<<endl;
	
	char ss[] = "1234567890";
	p1 = ss;
	p2 = ss+2;
	MemMove(p2, p1, 5);
	cout<<p1<<endl;
}
void test2(){
	char s[] = "1234567890";
	char* p1 = s;
	char* p2 = s+2;
	MemMove(p1, p2, 5);
	cout<<p1<<endl;
	
	char ss[] = "1234567890";
	p1 = ss;
	p2 = ss+2;
	MemMove(p1, p2, 5);
	cout<<p1<<endl;
} 
int main(){
	test(); 
	test2();
}
