#include<iostream>
#include<string.h>
char str1[100001],str2[100003];
void add(char a[])		
{
	strcat(str2,a);
}
int main()
{
	int n,i,b[11];
	char c[18][5]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111","00","0"};
	scanf("%d",&n); 
	char str[11][100001];
	while(n>0)
	{
	str1[0]='\0';
	str2[0]='\0';
	scanf("%s",str1);
	int a=strlen(str1);
	//十六进制转换为2进制 
	if(a%3==1)
	add(c[16]); 
	else if(a%3==2)
	add(c[17]);
	for(i=0;i<a;i++)
	{
		switch(str1[i])
		{
			case '0':add(c[0]);break;
			case '1':add(c[1]);break;
			case '2':add(c[2]);break;
			case '3':add(c[3]);break;
			case '4':add(c[4]);break;
			case '5':add(c[5]);break;
			case '6':add(c[6]);break;
			case '7':add(c[7]);break;
			case '8':add(c[8]);break;
			case '9':add(c[9]);break;
			case 'A':add(c[10]);break;
			case 'B':add(c[11]);break;
			case 'C':add(c[12]);break;
			case 'D':add(c[13]);break;
			case 'E':add(c[14]);break;
			case 'F':add(c[15]);break;
			default:break;
		}
	}
	//现在进行2进制转化为8进制 
	b[n]=strlen(str2);
	for(i=0;i<b[n];i+=3)
	{
		str[n][i]=(str2[i+2]-'0'+(str2[i+1]-'0')*2+(str2[i]-'0')*4)+'0';
		if(i==0&&str[n][i]=='0')
		continue;
		printf("%c",str[n][i]);
	}
	n--;
	printf("\n");
	}
	return 0;
}
