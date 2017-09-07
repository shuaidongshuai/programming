#include<stdio.h>
//整数的加减乘除   除法相当于 /  没有小数     不过正负包括了     小数等待开发 
// 注：整个代码除了 printf  有 + - * / 其余的地方     都不能出现 + - * / 
int add(int a,int b)
{
	int c;
	while(b!=0)				//直到没有进位 
	{
		c=(b^a);
		b=(b&a)<<1;			//如果b 不等于0   就说明有进位 
		a=c;
	}
	return c;
}
int sub(int a,int b)
{
	b=add(~b,1);		//  取b 的相反数 
	a=add(a,b);
	return a;
}
int mul(int a,int b)
{
	int c=0;
	if(b>0)
	{
		while(b)
		{
			c=add(c,a);
			b=sub(b,1);
		}
	return c;	
	}
	while(b)
	{
		c=add(c,a);
		b=add(b,1);
	}
	c=add(~c,1);
	return c;
}
int div(int a,int b)
{
	int count=0;
	while(a>=b)
	{
		a=sub(a,b);
		count++;
	}
	return count;
}
int divide(int a,int b)
{
	if(a<0&&b>0)
	{
		a=add(~a,1);
		return add(~div(a,b),1);
	}
	if(a>0&&b<0)
	{
		b=add(~b,1);
		return add(~div(a,b),1);		
	}
	if(a<0&&b<0)
	{
		a=add(~a,1);
		b=add(~b,1);
	}
	return div(a,b);
}
int main()
{
	int a,b;
	scanf("%d%d",&a,&b); 
	int c=add(a,b);
	int d=sub(a,b);
	int e=mul(a,b);
	int f=divide(a,b);
	if(b>0)
	{
	printf("%d+%d=%d\n",a,b,c);
	printf("%d-%d=%d\n",a,b,d);	
	printf("%d*%d=%d\n",a,b,e);	
	printf("%d/%d=%d",a,b,f);
	}
	else
	{
	printf("%d%d=%d\n",a,b,c);
	printf("%d-(%d)=%d\n",a,b,d);	
	printf("%d*(%d)=%d\n",a,b,e);	
	printf("%d/(%d)=%d",a,b,f);
	}
}

