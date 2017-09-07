#include<stdio.h>
int main()
{
	int i,x,y,sum=1;
	printf(" ‰»Îx y  ");
	scanf("%d%d",&x,&y); 
	for(i=0;i<y;i++)
	{
		sum=sum*x; 
	}
		if(sum>1000)
		{
			sum%=1000;
			if(sum>=100)
		printf("%d",sum);
		else if(sum>=10)
		printf("0%d",sum);
		else 
		printf("00%d",sum);
}
	else
	printf("%d",sum);
}
