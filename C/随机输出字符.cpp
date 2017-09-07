#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	int i,j;
	char ch;
	srand(time(NULL));
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			ch='A'+rand()%('Z'-'A');
			printf("%c\t",ch);
		}
			printf("\n");
	}
}
