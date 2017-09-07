#include <iostream>
#include <cstring>
using namespace std;

/*注意这里是连续的子串*/ 

char *longest_substring(char *str1,char *str2)
{
	if(!str1 || !str2)
		return NULL;
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int **arr = new int*[len1 + 1];
	for(int i = 0;i<len1 + 1;++i)
		arr[i] = new int[len2 + 1];
	for(int i = 0;i<len1 + 1;++i)
		arr[i][0] = 0;
	for(int j = 0;j<len2 + 1;++j)
		arr[0][j] = 0;
		
	//上面的代码都是初始化 
	int max = -1,x;
	for(int i = 1;i<len1+1;++i)
	{
		for(int j = 1;j<len2+1;++j)
		{
			if(str1[i - 1] == str2[j - 1])
				arr[i][j] = arr[i - 1][j - 1] + 1;
			else
				arr[i][j] = 0;
			if(arr[i][j] > max)
			{
				max = arr[i][j];
				x = i - 1;
			}
		}
	}
	char *substr = new char[max + 1];
	for(int i = max - 1; x >=0; --i)
	{
		substr[i] = str1[x--];
	}
	substr[max] = 0;
	return substr;
}

int main()
{
	char str1[100],str2[100];
	cin>>str1>>str2;
	cout<<longest_substring(str1,str2)<<endl;
}
/*
ashuaidong
adong
*/
