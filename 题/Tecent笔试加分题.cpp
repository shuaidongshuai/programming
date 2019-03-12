/*三 、加分题
28）给定一数组a[N]，我们希望构造数组b [N]，其中b[j]=a[0]*a[1]…a[N-1] / a[j]，在构造过程中，不允许使用除法：
要求O（1）空间复杂度和O（n）的时间复杂度；
除遍历计数器与a[N] b[N]外，不可使用新的变量（包括栈临时变量、堆空间和全局静态变量等）；
实现程序（主流编程语言任选）实现并简单描述。*/
#include <iostream>
using namespace std; 
void print(int arr[],int max)
{
	for(int i = 0;i<max;i++)
		cout<<arr[i]<<" "; 
}

int main()
{
	const int max = 5;
	int a[max] = {1,2,3,4,5};
	int b[max];
	b[0] = 1;
	for(int i = 1;i<max;i++)
		b[i] = b[i - 1] * a[i - 1];
	for(int i = max - 2; i >= 0; i--)
	{
		if(i != max - 2)
			a[max - 1] *= a[i + 1];
		b[i] *= a[max - 1];
	}
	print(b,max);
} 
