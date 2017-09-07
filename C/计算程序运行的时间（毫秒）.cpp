#include<stdio.h>
//#include<stdlib.h>
#include<time.h>
int  main(int argc, char *argv[])
{
    clock_t start,end;
	start=clock();
	int i,j,a[200][200];
    for(i=0;i<100;i++)
	for(j=0;j<100;j++)
	{
		a[i][j]=100*i+10*j;
		printf("%d\t",a[i][j]);
	}
    end=clock();
    printf("\n\n³ÌÐòÓÃÊ±%fs\n\a",(double)(end-start)/1000);
    return 0;
}
