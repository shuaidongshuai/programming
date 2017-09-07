#include<stdio.h>
int main()
{
	char a[100];
	int i;
	gets(a);		//这个例子充分说明了gets吧最后的换行符改成了'\0' 
	for(i=0;;i++)
	{
		if(a[i]!='*')
		printf("%c",a[i]);
		if(a[i]=='\0')	//从着看出 
		break;
	}
 } 
