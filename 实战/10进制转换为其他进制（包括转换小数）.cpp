#include<stdio.h>
#include<math.h>
void dong(int a,int b)
{
	int t;
	if(a!=0)
	{
		t=a%b;
		a=a/b;
		dong(a,b);
		printf("%d",t);
	}
}
int main()
{
	double a,c,d,e,f;
	int x,y,b;
	printf("请输入要转换的数和要转换的进制x,y\n");
	scanf("%lf%d",&a,&b);
	d=modf(a,&e);
	x=(int)e;
	dong(x,b);
	if(d!=0) printf(".");
	while(d!=0)
	{
		d=d*b;
		if(d>=1)
		{
		e=modf(d,&f);
		y=(int)f;
		printf("%d",y);
		d=e;
	}
	}
 } 
