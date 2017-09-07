#include<stdio.h>
#include<stdlib.h>
int (*p)[3]; 
void show(int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%10d",p[i][j]);
		}
		printf("\n");
	}
	printf("\n\t A         B         C\n\t~~~~~~~~~~~~~~~~~~~~~~~\n");
}
void move(char x,char y,int m)	//'A'=65 
{
	int i=x-65,j=y-65,temp,jmove,imove,q;
	for(q=0;q<m;q++)
	{
	if(p[q][i]!=0)
	{
		imove=q;
		break;
	}
    }
	for(q=m-1;q>=0;q--)
	{
	if(p[q][j]==0)
	{
		jmove=q;
		break;
	}
    }
    temp=p[imove][i];
    p[imove][i]=p[jmove][j];
    p[jmove][j]=temp;
	printf("%c->%c\n",x,y);
    show(m);
}
void hano(int n,char a,char b,char c,int m)
{
	if(n==1)
	{
		move(a,c,m);
	}
	else
	{
		hano(n-1,a,c,b,m);
		move(a,c,m);
		hano(n-1,b,a,c,m);
	}
}
int main()
{
	int i,j,n;
	printf("hano一共几个盘:");
	scanf("%d",&n);	
	p=(int (*)[3])malloc(n*3*sizeof(int ));
	if(NULL==p)
	{
		return 0;
	 }
	for(i=0;i<n;i++)
	{
		p[i][0]=i+1;
		printf("%10d",p[i][0]);
		for(j=1;j<3;j++)
		{
			p[i][j]=0;
			printf("%10d",p[i][j]);
		}
		printf("\n");
	}
		printf("\n\t A         B         C\n\t~~~~~~~~~~~~~~~~~~~~~~~\n");
		int m=n;
		hano(n,'A','B','C',m);

}
