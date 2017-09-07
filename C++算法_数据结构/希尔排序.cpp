#include <iostream>
using namespace std;

void display(int a[],int n)
{
	for(int i = 0;i<n;i++)
	{
		cout<<a[i]<<"  ";
	}
	cout<<endl;
}

void shellSort(int a[],int n) 
{
	int d = n/2;
	int temp,j;
	while(d>0)
	{
		for(int i = d;i<n;i++)
		{
			temp = a[i];
			for(j = i;j>0&&temp<a[j-d];j-=d)
			{
				a[j] = a[j-d];
			}
			a[j] = temp;
			display(a,9);
			//cout<<d<<endl;
		}
		d/=2;
	}
}

int main()
{
	int a[] = {8,5,6,7,4,9,1,2,3};
	shellSort(a,9);
	display(a,9);
}
