#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int arr[20];
void swap(int a,int b)
{
	int t= arr[a];
	arr[a]=arr[b];
	arr[b]=t;
}
void quick(int star,int end)
{
	int a=star,b=end;
	if(a<b)
	{
		while(1)
	{
		while(a<b&&arr[a]<arr[star]) a++;	//  不能写成 <= 如果这样最左边的值  是没有变化的一直都成立 
		while(a<b&&arr[b]>=arr[star]) b--;	//  必须写成 >= 不写的话会造成 如果有和第一个数相等的数  会出现死循环 
		if(a>=b) break;
		swap(a,b);
	}
	//有些快速排序法，有细微差别，这种排序，跳出循环有可能是 a = b+1  也有可能是 a=b 所以 下面 两个a-1 不能写成一个a-1 一个b+1 (不能同时出现a和b) 
	quick(star,a-1);
	quick(a+1,end);
	//注意两个 a-1 和 a+1 不能同时写成 a ，，都是a 的话 arr[a]这个数 既属于 左边 又属于 右边 这样程序就完全混乱了 
	}
}
int main()
{
	srand((unsigned )time(NULL));
	for(int i=0;i<20;i++)
	arr[i]=rand()%20;
	for(int j=0;j<20;j++)
	printf("%d  ",arr[j]);
	
	quick(0,19);
	printf("\n");
	for(int j=0;j<20;j++)
	printf("%d  ",arr[j]);
}    
