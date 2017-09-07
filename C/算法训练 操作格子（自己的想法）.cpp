//运行超时 20分   每次都要再加，不符合真正的 
#include<stdio.h>
#include<string.h>
int a[1000000],b[1000000];
int init(int l,int r,int i,int bo)
{
	if(r == l)
	a[i] = b[l];
	else
	{
		int mid = (l+r)/2;
		init(l,mid,2*i,bo);
		init(mid+1,r,2*i+1,bo);
		
		if(bo)
		a[i] = a[i*2] + a[2*i+1];
		else
		a[i] = a[2*i] > a[2*i+1] ? a[2*i] : a[2*i+1];
	}
}

int main()
{
	int n,m,i,j,x,y,z;
	scanf("%d%d",&n,&m);
    for(i = 1; i<=n; i++)
        scanf("%d",&b[i]);
    while(m--) 
	{
		scanf("%d%d%d",&x,&y,&z);

		if(x == 1)
			b[y] = z;		
		
		else if(x == 2)
		{
			init(y,z,1,1);
			printf("%d\n",a[1]);		
		}

		else if(x == 3)
		{
			init(y,z,1,0);
			printf("%d\n",a[1]);
		}
		memset(a,0,sizeof(a));
	}
	return 0;
}
