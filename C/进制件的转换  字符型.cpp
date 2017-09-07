#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
	//十进制转化为2进制		用整形转化 
	int t,b[100],n,i=0,j;
	scanf("%d",&n);
	while(n!=0)
	{
		t=n/2;
		b[i]=n%2;
		n=t;
		i++;
	 } 
	 for(j=i-1;j>=0;j--)
	 printf("%d",b[j]);
	 printf("\n\n");
	 //16进制转化为十进制转   用字符转换		节省空间内存 
	 char a[100];
	scanf("%s",a);
	int d=strlen(a);
	int sum=0;
	for(i=0;i<d;i++)
	{
		if(a[i]>='0'&&a[i]<='9')
		sum+=pow(16,i)*(a[i]-'0');
		else if(a[i]>='A'&&a[i]<='F')
		sum+=pow(16,i)*(a[i]-'A'+10);
		else if(a[i]>='a'&&a[i]<='f')
		sum+=pow(16,i)*(a[i]-'a'+10);
	 } 
	 printf("sum=%d\n",sum);
}
