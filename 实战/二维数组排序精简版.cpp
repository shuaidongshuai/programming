#include<stdio.h>
int main()
{
	int i,j,k,t,a[][4]={2,3,4,1,8,6,5,7,11,12,10,9,15,14,16,13};
	for(i=0;i<4;i++)
	for(j=0;j<3;j++)
	for(k=0;k<3-j;k++)
	if(i%2==1?a[i][k]<a[i][k+1]:a[i][k]>a[i][k+1])
	{
		t=a[i][k];
		a[i][k]=a[i][k+1];
		a[i][k+1]=t;
	}
	for(i=0;i<4;i++)
	{
	for(k=0;k<4;k++)
	printf("%5d",a[i][k]);
	printf("\n");
}
}
