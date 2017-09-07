#include<stdio.h>
#include<string.h>
char cmp[101];
int main()
{
	int i,j=0,len,min;
	char str1[102],str2[102],c;
	scanf("%s",str1);
	len=strlen(str1);
	strcpy(str2,str1);
	for(j=1;j<=len;j++)
	{
		c=str1[0];
		for(i=0;i<len-1;i++)
		{
			str1[i]=str1[i+1];
		}
		str1[i]=c;
		if(!strcmp(str1,str2))
		{
			printf("%d",j);
			break;
		}
		else if(j==len)
		printf("%d",j);
	}
	return 0;
 } 
