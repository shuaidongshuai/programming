#include <iostream>
#include <ctime>
using namespace std;
//剑指Offer——输入正整数S,打印出所有和为S的连续正数序列（至少含有两个正数）
//1 2 3 4 5 = 4 5 6 = 7 8 = 15
/*剑指offer上的解法,感觉书上代码不完美,自己修改了一下*/
void printadd(int min, int max, int sum)
{
	for (; min < max; min++)
		cout << min << " + ";
	cout << min << " = " << sum <<endl; 
}
void FindContinuousSequence(int n)
{
	int min = 0, max = 1, sum = 1;
	while(min <= n / 2)
	{
		if(sum == n)
		{
			printadd(min, max, sum);
			cout<<"--------------------------------------------------------------------"<<endl;
		}
		else if(sum > n)
		{
			sum -= min;
			++min;
			continue;
		}
		sum += ++max;
	}
}
void FindContinuousSequence2(int n)
{
	int min, max, count = 1, sum = 0;
	do
	{
		min = n / ++count - (count - 1) / 2;
		max = min + count - 1;
		for (int i = min; min>0 && i <= max; ++i)
			sum += i;
		if (sum == n)
		{
			printadd(min, max, sum);
			cout<<"--------------------------------------------------------------------"<<endl;
		}
		sum = 0;
	} while (min > 0);
}

void test1(int a)
{
	struct timeb startTime , endTime;
	ftime(&startTime);
	FindContinuousSequence(a);
	ftime(&endTime);
	cout << "test1耗时：" << (endTime.time-startTime.time)*1000 + (endTime.millitm - startTime.millitm) << "毫秒" << endl;  
} 
void test2(int a)
{
	struct timeb startTime , endTime;
	ftime(&startTime);
	FindContinuousSequence2(a);
	ftime(&endTime);
	cout << "test2耗时：" << (endTime.time-startTime.time)*1000 + (endTime.millitm - startTime.millitm) << "毫秒" << endl;  
}
int main()
{
	//int a = 0x7ffff;
	int a = 43124321;
	test1(a);
	cout<<"============================================================================="<<endl; 
	test2(a);
	cout<<"============================================================================="<<endl; 
}
