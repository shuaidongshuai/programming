#include <iostream>
using namespace std;

int main1()
{
	int a = 10;
	int b = 20;
	int c = 30;
	int d = 40;
	int e = 50;
	return 0;
}
/*
int a = 10;
0009555E  mov         dword ptr [ebp-8],0Ah			vs2013中第一个变量在 ebp-8的位置
int b = 20;
01393C75  mov         dword ptr [ebp-14h],14h								-20
int c = 30;
01393C7C  mov         dword ptr [ebp-20h],1Eh								-32
int d = 40;
01393C83  mov         dword ptr [ebp-2Ch],28h								-44
int e = 50;
01393C8A  mov         dword ptr [ebp-38h],32h								-56
*/