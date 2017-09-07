#include<stdio.h>
#include<string.h>
char *Strcat(char *a,char *b){
	char *c,*p;
	c = p = a;
	while(*c++ = *a++);
	while(*c++ = *b++);
	return p;
} 
int main(){
	char a[] = "hello ";
	char b[] = "world!";
	
	printf("%s\n",strcat(a,b));
	
	printf("%s\n",Strcat(a,b));
}
