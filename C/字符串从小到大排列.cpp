#include<stdio.h>
#include<string.h>
int main()
{
	char a[4][20],c[20];
	int i,j,k;
	for(i=0;i<4;i++)
	{
		gets(a[i]);
	}
	for(i=0;i<3;i++)
	{
		i=k;
		for(j=i+1;j<4;j++)
		{
			if(strcmp(a[j],a[k])<0)
			{
				k=j;
			}
		}
		if(i!=k)
		{
			strcpy(c,a[i]);
			strcpy(a[i],a[k]);
			strcpy(a[k],c);
		}
	}
	printf("Êä³ö£º\n");
	for(i=0;i<4;i++)
	puts(a[i]);
}
