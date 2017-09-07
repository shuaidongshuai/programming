#include<stdio.h>
#include<time.h>
#include<stdlib.h>
// merge  融入 
// 归并的思想就是 利用 两个有序数组合并 的原理（合并是有规则的，不是简单相加） 
// 但是给定的数组不是有序  ！！求的就是把数列从小到大排列出来 
// 每次把 数列 砍成一半  前一半 和后一边 进行归并  但是有可能 这两半数列还是没有序的
// 典型的递归  想办法把数列 给有序化     可以想到！！！当一个数组只有一个数的时候  那肯定就是有序的！！！ 
void mergearrage(int arr[],int start,int mid,int end,int temp[])
{
	int a,b,c,k=0;
	a=start;
	b=mid+1;
	while(a<=mid&&b<=end)			// b +1  就意味着吧 mid  算成了前面那个数列 
	{
		if(arr[a]>arr[b])
		temp[k++]=arr[b++];
		else
		temp[k++]=arr[a++];
	}
	while(a<=mid)
	temp[k++]=arr[a++];
	
	while(b<=end)
	temp[k++]=arr[b++];
	
	int i;
	for(i=0;i<k;i++)
	arr[start+i]=temp[i];		//  这样的代码只有自己打才会知道  精髓所在  啊   刚开始 start + i  填成了 i   一直不行 
}
 
void mergesort(int arr[],int start,int end,int temp[])
{
	if(start<end)					// start代表一个数列的第一个  end 代表数列的最后一个   我们需要的就是数列只有一个数  就只有第一个数就是最后一个数的时候 
	{																					// 当 start ==  end 的时候 递归就不执行 了 
		int mid=(start+end)/2;
		mergesort(arr,start,mid,temp);//向左   实现把大数列化成小数列  知道最后化成一个数  的数列 
		mergesort(arr,mid+1,end,temp);//向右   同理 
		mergearrage(arr,start,mid,end,temp);//把只含有一个数的  两个数列合并  然后 把含有两个数的 两个数列合并  知道  完整的数列 
	}
 } 
 
// 下面的代码就不属于 归并了 
int main()
{
	int i,a[100],b[100];
	srand(time(NULL));		// 获取随机数种子 
	for(i=1;i<=50;i++)
	{
		a[i]=rand()%10+10;
		printf("%d\t",a[i]);
		if(i%10==0)
		printf("\n");
	}
	mergesort(a,1,50,b);
	printf("\nThe following are sorted\n\n\a");
	for(i=1;i<=50;i++)
	{
		printf("%d\t",a[i]);
		if(i%10==0)
		printf("\n");
	}
 } 
