#include<stdio.h>
char replace(char *s1,char *s2,int p)
{
	int i,j;
	i=0;
	for(j=p;s1[j]!='0';j++)
	{
		s1[j]=s2[i];
		i++;
	}
	return s1[100];
}
int main()
{
	char s1[100],s2[100];
	gets(s1);					/* ‰»Îtoday is mondayªÿ≥µfriday*/
	gets(s2);
	replace(s1,s2,9);
	printf("%s",s1);
 } 
