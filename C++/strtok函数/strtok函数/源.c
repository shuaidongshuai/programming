#define  _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <cstring>
//using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	char str[] = "username=dong&score=100";
	printf("%s", strtok(str, "=&"));
	char* p;
	while (p = strtop(NULL, "=&"))
		printf("%s\n", p);

	getchar();
}
void main1(){
	char s[] = "ab-cd : ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
	char *delim = "-: ";
	char *p;
	//printf("%s ", strtok(s, delim));
	char* fen = "-";
	printf("%s ", strtok(s,fen));
	while ((p = strtok(NULL, fen)))
		printf("%s\n", p);

	getchar();
}