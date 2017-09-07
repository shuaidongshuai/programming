#include<stdio.h>
#include<stdlib.h>
int main()
{
	int (*p)[3],i,j,n;//n 行  3 列 的指针数组     这样就不能由用户输入 列  虽然dev C++用这种方法可以行列都由用户输入   但很多编译器不行    
	scanf("%d",&n);
	p=(int (*)[3])malloc(n*3*sizeof(int));
	for(i=0;i<n;i++)
	{
		for(j=0;j<3;j++)
		{
			p[i][j]=i+j;
			printf("%5d",p[i][j]);
		}
		printf("\n"); 
	}
}
