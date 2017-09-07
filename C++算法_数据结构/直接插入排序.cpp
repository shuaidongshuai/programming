#include <iostream>
using namespace std;

void display(int a[],int n)
{
	for(int i = 0;i<n;i++)
	{
		cout<<a[i];
	}
}
void zijieInsert(int a[],int n)
{
	int temp,j;
	for(int i=1;i<n;i++)
	{
		temp = a[i];
		for(j = i;j>0&&temp<a[j-1];j--)//当前元素比上前一个元素要小 
		{
			a[j] = a[j-1];//前一个往后移动 
		}
		a[j] = temp;//把比较元素放在 它应该处于的位置 
		display(a,9);
		cout<<endl;
	}
}

int main()
{
	int a[] = {8,5,6,7,4,9,1,2,3};
	zijieInsert(a,9);
	display(a,9);
}
