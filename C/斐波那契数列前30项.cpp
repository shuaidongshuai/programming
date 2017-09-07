#include<stdio.h>
int main()
{
	int a=1,t,b=1,c,i;
	printf("1\t1\t");
	for(i=3;i<31;i++)
	{
		t=a;
		a=a+b;
		b=t;
		printf("%d\t",a);
		if(i%5==0) printf("\n"); 
	}
	//上面是自己做的，下面是书上的。书上的好理解点
	int w[30];
	w[1]=1,w[2]=1;
	printf("1\t1\t");
	for(i=3;i<31;i++)
	{
		w[i]=w[i-1]+w[i-2];
		printf("%d\t",w[i]);
		if(i%5==0) printf("\n");
	 } 
 } 
