#include<stdio.h>
int news[2015];
int main()
{
	int i,j,n;
	scanf("%d",&n);
	char input[1500][10],num[1500];
	for(i=1;i<=n;i++)
	{
		scanf("%s",input[i]);
		if(input[i][0]=='D')
		scanf("%d",&num[i]);
	}
	for(i=1;i<=n;i++)
	{
		if(input[i][0]=='N')
		for(j=1;j<=n;j++)
		{
			if(news[j]==0)
			{
				news[j]=j;
				printf("%d\n",j);
				break;
			}
		}
		else if(input[i][0]=='D')
		{
			if(news[num[i]]!=0)
			{
				printf("Successful\n");
				news[num[i]]=0;				
			}
			else
			printf("Failed\n");
		}
	}
	return 0;
 } 
