#include<stdio.h>
int main()
{
	FILE *p;
	p=fopen("stdent.dat","wb");
	char o,st[3];
	int i;
	for(i=0;i<3;i++)
	{
	scanf("%s",&st[i]);
	o=getchar();
}
	fwrite(st,sizeof(st[3]),3,p);
 } 
