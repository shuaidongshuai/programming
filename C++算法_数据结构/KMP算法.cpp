#include <iostream>
#include <cstring>
using namespace std;

//在了解KMP算法之前必须先了解bf算法

int bf(char *str, char *substr, int index)	// index是用户指定从str这个串中任意位置开始匹配
{
	int slen = strlen(str);
	int sublen = strlen(substr);
	int i = index;
	int j = 0;
	while (j<sublen)
	{
		if (i >= slen)
			return -1;
		if (str[i] == substr[j])
		{
			i++; j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	return i - j;
}
//KMP算法
//  a b c a b c a b c a b c d a b c d e
//  x 0 0 0 1 2 3 4 5 6 7 8 9 0 1 2 3 0
//////////////////////////////////////////////////////////////////////////////////////////////////
/* 下面next数组中记录的是：这次匹配失败之后，j应该回退到k位置去    注意：i不会回退*/
void getNext(char *substr, int *&next)
{
	int sublen = strlen(substr);
	if (sublen == 0)
		return;
	next = new int[sublen];
	next[0] = -1;//第一个角标我们默认初始化为-1 
	if (sublen == 1)
		return;
	next[1] = 0;//第二个角标初始化为0
	 
	/*弄两个角标出来，一前一后，求的是i + 1位置匹配失败应该回退的位置*/ 
	int i = 1, k = 0; 
	while (i < sublen)
	{
		if (-1 == k || substr[k] == substr[i])// i + 1 位置匹配失败但是 i 位置和 k 位置字符相等 
			next[++i] = ++k;
		// else				//				   如果出现 a b c a b a b c
			// next[i] = 0; 				//	   	   -1 0 0 0 1 2 1 2  所以并不是每次都回到 0 位置  这里就回到了1 
		else
			k = next[k];// i+1位置上匹配失败了，并且i 位置 和 k 位置不相等，我们就要回退到 “k位置匹配失败”后回退的位置上去
						//就相当于把k以前的串当成了子串，i以前的串当成了父串 【为什么可以这样做？k位置匹配失败回退的位置我们已经知道了,k是小于i的】 
	}
}
int KMP1(char *str, char *substr, int index)
{
	int slen = strlen(str);
	int sublen = strlen(substr);
	int i = index;
	int j = 0;
	int *next;
	getNext(substr, next);
	while (j<sublen)
	{
		if (i >= slen)
			return -1;
		if (-1 == j || str[i] == substr[j])
		{
			i++; j++;
		}
		else
			j = next[j];
	}
	return i - j;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
下面nextVal是next的升级版本 当出现substr="aaaaab" 这种情况比上面更高效
										  x01234  
	当str = "aaaacaaaaab" 我们匹配到c的时候失败，如果是next那么应该跑到k = 3的位置上去，
	但实际上3位置也是‘a’，下次比较就属于无效比较，还是会再次回到上一个k,所以有了nextVal进行优化		a a a a a b a a b a
																									   -1 0 0 0 0 1 0 0 2 0
*/
void getNextVal(char *substr, int *&nextVal)
{
	int sublen = strlen(substr);
	if (sublen == 0)
		return;
	nextVal = new int[sublen];
	nextVal[0] = -1;
	if (sublen == 1)
		return;
	nextVal[1] = 0;
	int i = 1;
	int k = 0;
	while(i<sublen)
	{
		if(-1 == k || substr[k] == substr[i]) 
		{
			if(substr[i + 1] == substr[i])
				nextVal[i + 1] = nextVal[i];
			else
				nextVal[i + 1] = ++k;
			++i;
		}
		else
			k = nextVal[k];
	}
}
int KMP2(char *str, char *substr, int index)
{
	int slen = strlen(str);
	int sublen = strlen(substr);
	int i = index;
	int j = 0;
	int *nextVal;
	getNextVal(substr,nextVal);
	while (j<sublen)
	{
		if (i >= slen)
			return -1;
		if (-1 == j || str[i] == substr[j])
		{
			i++; j++;
		}
		else
		{
			j = nextVal[j];
		}
	}
	return i - j;
}
int main()
{
	char *str = "ababcabcdabcde";
	char *substr = "abcd";
	int res = bf(str, substr, 0);
	cout << "bf :" << res << endl;
	res = bf(str, substr, 6);
	cout << "bf :" << res << endl;

	res = KMP1(str, substr, 0);
	cout << "KMP :" << res << endl;
	res = KMP1(str, substr, 6);
	cout << "KMP :" << res << endl;

	str = "aaabcaaabcabcf";
	substr = "aaabcabcf";
	//		  x001230
	res = KMP1(str, substr, 0);
	cout << "KMP1 :" << res << endl;

	res = KMP2(str, substr, 0);
	cout << "KMP2 :" << res << endl;
}
