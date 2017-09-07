#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	wchar_t t;
	srand(time(NULL));
	for(int i=1;i<=100;i++)
	{
		t='A'+rand()%26;
		printf("%c\t",t);
		if(i%10==0)
		{
			printf("\n");
		}
	}
	printf("\n");
	for(int j=1;j<=100;j++)
	{
		t='A'+rand()%26+32;
		printf("%c\t",t);
		system("pause");
	}
 } 
