#include<stdio.h>
struct dong
{
	void (*nand_reset)(void);		// nand_reset 必须放在 (* )里面     下面会有解释 
}nand_chip;
//如果上面  加上 typedef {}t_nand_chip  下面就把注释去掉      其实就是加上了 typedef 后 （dong 就可以去掉了）   struct dong 就相当于 t_nand_chip 
//t_nand_chip nand_chip;
void s3c2440_nand_reset(void)
{
	printf("hello dong\n");
}
void nand(void)		
{
    nand_chip.nand_reset();
}
int main1()
{
	nand_chip.nand_reset=s3c2440_nand_reset;
	nand();
 } 
 // 由于嵌入式比较复杂 如果要让一段代码有通用性   有时候就有这样绕圈子的代码 
 //先从  nand中调用结构体中的 nand.reset这个函数指针  而这个函数指针又指向 s3c2440 
  
 
 // 根据上面  下面是百度的例子 
 //C语言技巧--在结构体中使用函数例子（定义一个指向函数的指针） .这里就解释了 为什么 函数要放在（* ）里面了 
  
#include <malloc.h>   
#include <memory.h>   
#define DECLARATION int (*ptr)(int x,int y)   
#define DEFINITION(x,y) ptr(x,y)   
int sum(int x,int y)
{   
 printf("x:%d\n",x);
 printf("y:%d\n",y);

    return(x+y);   
}
int mul(int a,int b)
{
	return a*b;
}
typedef struct {  
        int r;  
  int (*ptr)(int x,int y);   //这只是一个指针，可以指向任何  有两个整形参数的函数 
} mystr;  
int main()  
{  
    int a,b,c;  
    scanf("%d%d",&a,&b);  
    mystr stru;    
  	
	stru.ptr=sum;   
	c=stru.ptr(a,b); 
    printf("a=%d,b=%d,sum=%d\n",a,b,c);
    
    stru.ptr = mul;
    c=stru.ptr(a,b);
    printf("mul = %d",c);
      
    /* mystr *stru1;   */
    /* stru1=(mystr *)malloc(sizeof(mystr));   */
    /* memset(stru1,0,sizeof(mystr));   */
    /* c=stru1->DEFINITION(a,b); */

 
  
    /* //c=stru->ptr(a,b);    */
    /* printf("a=%d,b=%d,sum=%d\n",a,b,c);   */
 /* memset(stru1,0,sizeof(mystr));   */
 /* free(stru1);  xz */
}   
