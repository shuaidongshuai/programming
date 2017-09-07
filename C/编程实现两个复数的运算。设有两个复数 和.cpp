#include<stdio.h>
#include<stdlib.h>
typedef struct str
{
	float a;
	float b;
}*dong,jg;
dong sum(jg x,jg y)
{
	dong c=(jg *)malloc(sizeof(jg));
	c->a=x.a+y.a;
	c->b=x.b+y.b;
	return c;
}
dong sub(jg x,jg y)
{
	dong c=(jg *)malloc(sizeof(jg));
	c->a=x.a-y.a;
	c->b=x.b-y.b;
	return c;
}
dong mul(jg x,jg y)
{
	dong c=(jg *)malloc(sizeof(jg));
	c->a=x.a*y.a;
	c->b=x.b*y.b;
	return c;
}
dong divide(jg x,jg y)
{
	dong c=(jg *)malloc(sizeof(jg));
	c->a=x.a/y.a;
	c->b=x.b/y.b;
	return c;
}
int main()
{
	char n;
	jg x,y;
	dong z=(jg *)malloc(sizeof(jg));	
	scanf("%c",&n);
	scanf("%f%f%f%f",&x.a,&x.b,&y.a,&y.b);
	if(n=='+')
	z=sum(x,y);
	else if(n=='-')
	z=sub(x,y);
	else if(n=='*')
	z=mul(x,y);
	else if(n=='/')
	z=divide(x,y);
	printf("%.2f+%.2fi",z->a,z->b);
	return 0;
}
