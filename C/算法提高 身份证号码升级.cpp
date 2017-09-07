#include<stdio.h>
int main()
{
	int i,sum=0,c[17]={7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
	char a[18];
	for(i=0;i<17;i++)
	{
		if(i==6)
		a[6]='1';
		else if(i==7)
		a[7]='9';
		else
		scanf("%c",&a[i]);
		sum+=(a[i]-'0')*c[i];
	}
	int b=sum%11;
	if(b==0)
	a[i]='1';
	else if(b==1)
	a[i]='0';
	else if(b==2)
	a[i]='x';
	else if(b==3)
	a[i]='9';
	else if(b==4)
	a[i]='8';
	else if(b==5)
	a[i]='7';
	else if(b==6)
	a[i]='6';
	else if(b==7)
	a[i]='5';
	else if(b==8)
	a[i]='4';
	else if(b==9)
	a[i]='3';
	else if(b==10)
	a[i]='2';
	for(i=0;i<18;i++)
	printf("%c",a[i]);
}
