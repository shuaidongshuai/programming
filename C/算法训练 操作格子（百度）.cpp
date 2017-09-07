#include <stdio.h>
int max(int a,int b)
{
	return a>b?a:b;
 } 
struct node
{
    int l,r,n,sum;
} a[1000000];

void init(int l,int r,int i)
{
    a[i].l = l;
    a[i].r = r;
    a[i].n = 0;
    a[i].sum = 0;
    if(l!=r)
    {
        int mid = (l+r)/2;
        init(l,mid,2*i);
        init(mid+1,r,2*i+1);
    }
}
void insert(int i,int x,int m)
{
    if(x>=a[i].l && x<=a[i].r)
    {
        a[i].n=m;
        a[i].sum=m;
    }
    if(a[i].l == a[i].r)
        return ;
    int mid = (a[i].l+a[i].r)/2;
    if(x>mid)
        insert(2*i+1,x,m);
    else
        insert(2*i,x,m);
        a[i].sum = a[2*i].sum+a[2*i+1].sum;
        a[i].n = max(a[2*i].n,a[2*i+1].n);
}

int find_max(int x,int y,int i)
{
    if(x == a[i].l && y == a[i].r)
    return a[i].n;
    int mid = (a[i].l+a[i].r)/2;
    if(x>mid)      return find_max(x,y,2*i+1);
    else if(y<=mid)     return find_max(x,y,2*i);
    else
        return max(find_max(x,mid,2*i),find_max(mid+1,y,2*i+1));
}

int find_sum(int x,int y,int i)
{
    if(a[i].l == x && a[i].r == y)
        return a[i].sum;
    int mid = (a[i].l+a[i].r)/2;
    if(x>mid)
        return find_sum(x,y,2*i+1);
    else if(y<=mid)
        return find_sum(x,y,2*i);
    else
        return find_sum(x,mid,2*i)+find_sum(mid+1,y,2*i+1);
}

int main()
{
    int n,m,i,j,b,x,y,cas;
    scanf("%d%d",&n,&m);
    init(1,n,1);
    for(i = 1; i<=n; i++)
    {
        scanf("%d",&b);
        insert(1,i,b);
    }
    while(m--)
    {
        scanf("%d%d%d",&cas,&x,&y);
        if(cas==1)
            insert(1,x,y);
        else if(cas==2)
            printf("%d\n",find_sum(x,y,1));
        else if(cas==3)
            printf("%d\n",find_max(x,y,1));
    }

    return 0;
}

