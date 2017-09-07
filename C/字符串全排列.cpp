#include <iostream>
#include <cstring>
using namespace std;

void swap(char *a, char *b)
{
	char t = *a;
	*a = *b;
	*b = t;
}
//下面这样是不行的                           为什么呢？写两个测试代码就知道了 
//void perm(char *str, int start, int end)
//{
//	if (start >= end)
//		cout << str << endl;
//	else
//		for (int i = start ;i <= end ; i++)
//		{
//			if(str[start] != str[i] || start == i)
//			{
//				swap(str+start,str + i);
//				perm(str,start + 1,end);
//				swap(str+start,str + i);
//			} 
//		}
//}

//在交换之前判断一下，end的前面有木有和自己一样的数，有的话就不交换了
bool IsSwap(char *arr,int start,int end)
{
	while(start < end)
		if(arr[start++] == arr[end])
			return false;
	return true;
}
void perm(char *str, int start, int end)
{
	if (start >= end)
	{
		static int i = 1;
		cout << i++ << ":" << str << endl;
	}
	else
		for(int i = start; i <= end; i++)
			if(IsSwap(str,start,i))
			{
				swap(str+start,str + i);
				perm(str,start + 1,end);
				swap(str+start,str + i);	
			}
}
int main()
{
	char str[] = "1100";
	perm(str, 0, strlen(str) - 1);
}
