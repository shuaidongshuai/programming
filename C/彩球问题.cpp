#include<stdio.h>
int main()
{
	printf("time    \tred ball\twhile ball\tblack ball\n");
	int hong=3,bai=3,hei=6,n=0;
	for(hong=0;hong<4;hong++)
	for(bai=0;bai<4;bai++)
	for(hei=0;hei<7;hei++)
	if(hong+bai+hei==8)
	{
		n++;
		printf("%d\t\t%d\t\t%d\t\t%d\n",n,hong,bai,hei);
	}
}
