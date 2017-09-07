#include<iostream>
#include<memory.h>
#define MAX 1000010
#define N 100010
using namespace std;
int C1[MAX],C2[MAX],b[MAX];
int num[N];
long long total[N],ans;
int lowbit(int x)
{
	return x&(-x);
}
void add(int pos,int num,int *C)
{
	while(pos<=MAX)
	{
		C[pos]+=num;
		pos+=lowbit(pos);
	}
}
int Sum(int pos,int *C)
{
	int sum=0;
	while(pos>0)
	{
		sum+=C[pos];
		pos-=lowbit(pos);
	}
	return sum;
}
void init()
{
	total[0]=0;
	for(int i=1;i<=N;i++)
	{
		total[i]=total[i-1]+i;
	}
}
int main()
{
	int i;
	init();
	memset(C1,0,sizeof(C1));
	memset(C2,0,sizeof(C2));
	int n;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>num[i];
		add(num[i]+1,1,C1);
		
		//cout<<i<<endl;
		//cout<<Sum(num[i],C1)<<endl;
		//cout<<Sum(num[i]-1,C1)<<endl;
		//cout<<endl;
		
		b[i]=i-Sum(num[i],C1);
		b[i]=b[i]-(Sum(num[i]+1,C1)-Sum(num[i],C1)-1);
	}
	
	//for(int j=0;j<20;j++)
	//	cout<<C1[j]<<' ';
	//	cout<<endl;
	
	for(i=n-1;i>=0;i--)
	{
		add(num[i]+1,1,C2);
		b[i]=b[i]+Sum(num[i],C2);
		
	}
	
	//for(int j=0;j<20;j++)
	//	cout<<b[j]<<' ';
	//	cout<<endl;
	
	ans=0;
	for(i=0;i<n;i++)
	{
		ans+=total[b[i]];
	}
	cout<<ans<<endl;
	return 0;
 } 
