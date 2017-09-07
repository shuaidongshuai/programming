#include<iostream>
#include <cstring>
using namespace std;

void getLast(char *pre, char *mid, char *&last, int n,int &index)
{
	if (!pre || !mid || n <= 0)
		return;
	int i = 0;
	for (; i < n; i++)
	{
		if (*pre == *(mid + i))
			break;
	}
	last[index--] = *pre;
	getLast(pre + i +1, mid + i + 1, last, n - i - 1, index);
	getLast(pre + 1, mid, last, i, index);
}
char *getLast(char *pre, char *mid, int n)
{
	if (!pre || !mid || n <= 0)
		return NULL;
	char *last = new char[n + 1];
	int index = n - 1;
	getLast(pre, mid, last, n, index);
	last[n] = 0;
	return last;
}
int main()
{
	char *str1 = "ABDECFG";
	char *str2 = "DBEAFCG";
	cout << getLast(str1, str2, strlen(str1)) << endl;
	system("pause");
}