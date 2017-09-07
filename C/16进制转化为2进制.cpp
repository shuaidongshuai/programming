#include<iostream>
#include<string.h>
char str1[100001],str2[100003];
void add(char a[])		
{
	strcat(str2,a);
}
int main()
{
	int n,i;
	char c[18][5]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
	while(1)
	{
		str1[0]='\0'; 
		str2[0]='\0'; 
		scanf("%s",str1);
		int a=strlen(str1);
	//十六进制转换为2进制
	
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
		//printf("%s\n",str2);
	}
	printf("%s\n",str2);
}

}





 
