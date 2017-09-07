#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main()
{
	int i,a[10],t;
	srand(time(NULL));
	printf(" ‰»Î÷Æ«∞£∫\n");
	for(i=0;i<10;i++)
	{
	a[i]=rand()*100/32767;
	printf("%d\t",a[i]);
}
printf("\n≈≈–Ú£∫\n");
	for(i=0;i<5;i++)
	{
		t=a[i];
		a[i]=a[9-i];
		a[9-i]=t;
	}
	for(i=0;i<10;i++)
			printf("%d\t",a[i]);
}
