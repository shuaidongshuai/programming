#include<stdio.h>
void dong(int a,int b)
{	
	int shang=a,yu;
	if(shang!=0)
	{
		yu=a%b;
		shang=a/b;
		dong(shang,b);
		printf("%d",yu);
	}
}
int main()
{
	int a,b;
	printf("输入一个十进制数:\n输入要转换的数:\n");
	scanf("%d%d",&a,&b);
	dong(a,b);
}

