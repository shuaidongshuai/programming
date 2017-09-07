#include<stdio.h>
//有左右脚的限制。
const int N=39;
int f(int m,int n)
{
	if(m==0||n==0)
		return 1;
	
	return(f(m-1,n)+f(m,n-1));//递归的关键在此，大规模逐渐转化为小规模。
}

int main()
{
	int x=N/2,y;		//x表示走两步的次数，y表示走一步的次数。
	int i,sum=0;
	
	for(i=x;x>=0;x-=2)		//为了保持偶数步，必须x每次递减2，而不是1；(x要x>=0,不能x>0)，x=0是针对偶数台阶。
	{
		y=N-2*x;
		sum+=f(x,y);		//求组合数;
	}
	printf("%d",sum);
	return 0;
}
