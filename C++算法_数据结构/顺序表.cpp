#include<stdio.h>
#include<malloc.h>
#define status int
struct sqlist
{
	int * elem;				//储存空间地址 
	int length;				//当前长度 
	int listsize;			//最大内存容量 
};
//顺序量表初始化
void initlist(sqlist &l)
{
	l.elem=(int *)malloc(10*sizeof(int ));
	if(!l.elem)
	printf("overflow");
	else
	{
		l.length=0;
		l.listsize=10;			//默认储存容量为 10 
		printf("OK\n");
	}
}
//插入数据
status listinsert(sqlist &l,int i,int e)		// e 位新增元素    i 为插入的位置 
{
	int *p,*q,*newbase;
	if(i<1|| i>l.length+1)
	{
		printf("%d error\n",i);
		return 0;
	}
	if(l.length>=l.listsize)
	{
		//申请一个更大的空间
		newbase=(int *)realloc(l.elem,(l.listsize+2)*sizeof(int ));
		 if(!newbase)
		 {
		 	printf("overflow\n");
		 	return 0;
		 }
		 l.elem=newbase;
		 l.listsize+=2;
	}
	q=&(l.elem[i-1]);   					 //  q  为插入位置 
	for(p=&(l.elem[l.length -1]);p>=q;p--)	//向后移动  直到 q  
	*(p+1)=*p;
	*q=e;									//新增元素 
	l.length++;						//表长 加一 
	return 1; 
}
// 判断当前顺序表是否为空   为空 返回1 否则 返回0 
status listempty(sqlist l)
{
	if(l.length==0)
	return 1;
	else
	return 0;
}
//清空顺序表
void clearlist(sqlist &l)
{
	l.length=0;
 } 
 //求顺序表中元素的个数
 int listlength(sqlist l)
 {
 	return l.length;
  } 
  status listdelete(sqlist &l,int i)			//删除
 {
 	int *p,*q;
 	if(i<1|| i>l.length)
 	{
 		printf("i error\n");
 		return 0;
	 }
	 p=&(l.elem[i-1]);			//p   为被删元素的位置
	 q=l.elem+l.length-1;		//*********************开始还没看懂    这是q 指向表尾的位置
	 for(p++;p<=q;p++)
	 *(p-1)=*p;
	 l.length--;			//表长减 1
	 return 1; 
  } 
 int main()
 {
 	status i;
 	int a,j,k,e;
 	sqlist l;
 	initlist(l);
 	printf("初始化l后：l.elem=%u\tl.length=%d\tl.listsize=%d\n",l.elem,l.length,l.listsize);	// %u 无符号十进制输出 
 	printf("请在表头先插入5个数\n");
 	for(j=1;j<=5;j++)
 	{
 		scanf("%d",&a);
 		i=listinsert(l,1,a);
	 }
	 
	 printf("原始数据为:\n");
	 for(j=0;j<5;j++)
	 {
	 	printf("%d\t",*(l.elem+j));
	  } 
 	printf("\nl.elem=%u\tl.length=%d\tl.listsize=%d\n",l.elem,l.length,l.listsize);
 	clearlist(l);
 	printf("清空后：l.elem=%u\tl.length=%d\tl.listsize=%d\n",l.elem,l.length,l.listsize);
 	printf("在表尾插入l.elem=");
	for(j=5;j>0;j--)
	i=listinsert(l,1,j);
 	for(j=0;j<5;j++)
 	printf("%d\t",*(l.elem+j));
 	printf("\n");
 	k=listlength(l);
	for(j=k;j>0;j--)
	{
		printf("dong  ");
		i=listdelete(l,j);
		if(i==0)
		printf("error ");
		else
		printf("删除第%d个元素成功:%d\n",j,l.elem[j-1]); 
	 } 
}
