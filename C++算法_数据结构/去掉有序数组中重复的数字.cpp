#include <iostream> 
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

/* 去掉有序数组中重复的数字 并返回去掉重复数组的长度*/
/* 要求不能另外开辟数组 */ 

/* 每次都判断当前位置index 和i是否一样 不一样就把下一个位置赋值为i */ 
int removeDuplicates(vector<int> &v)
{
	int index = 0;
	for(int i = 1;i<v.size();++i)
	{
		if(v[index] != v[i])
			v[++index] = v[i];
	}
	return index + 1;
} 

/* 那如果可以重复两个数呢？ */ 
/* 和上面原理一样 上面是把下一个位置赋值为i 这里是把下2两个位置赋值为1 */
int removeDuplicates2(vector<int> &v)
{
	int index = 2;
	for(int i = 2;i<v.size();++i)
	{
		if(v[index - 2] != v[i])
			v[index++] = v[i];
	}
	return index;
}
/* 那如果可以重复N个数呢？ */ 
int removeDuplicatesN(vector<int> &v,int n)
{
	int index = n;
	for(int i = n;i<v.size();++i)
	{
		if(v[index - n] != v[i])
			v[index++] = v[i];
	}
	return index;
}
/*下面这样容易理解*/ 
int removeDuplicates22(vector<int> &v)
{
	int index = 0;
	for(int i = 2;i<v.size();++i)
	{
		if(v[index] != v[i])
			v[index++ + 2] = v[i];
	}
	return index + 2;
} 
int removeDuplicatesNN(vector<int> &v,int n)
{
	int index = 0;
	for(int i = n;i<v.size();++i)
	{
		if(v[index] != v[i])
			v[index++ + n] = v[i];
	}
	return index + n;
}

int main()
{
	vector<int> v;
	for(int i = 0;i<10;++i)
		v.push_back(rand()%4);
	cout<<"原数组"<<endl;
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;
	
	cout<<"排序后的数组"<<endl;
	sort(v.begin(),v.end());
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
	cout<<endl;
	
	cout<<"去掉重复后的数组"<<endl;
	int len = removeDuplicatesNN(v,2);
	copy(v.begin(), v.begin() + len, ostream_iterator<int>(cout, " "));
}
