#include "iostream"
using namespace std;
int main(){
    int a=0;
    printf("%d %d %d",a++,a++,a++);//从左往右开始进栈，才能保证出栈是从左往右，a先进栈再加1，再进栈 再加1 在进栈再加1
	printf("\n%d\n",a);			   //这样就能解释 这个额 a 为什么3    
    int b=1;
    printf("\n%d %d %d",++b,++b,++b);//因为加号全部在前面 都是先执行加1 然后再进栈  所以最后输出来的都一样 
    printf("\n%d %d %d %d",++b,++b,++b,++b);//充分证明上一步解释是正确的
    int c=1;
    printf("\n%d %d %d",++c,++c,c++);
    int d=1;
    printf("\n%d %d %d",d++,++d,d++);
    int e=1;
    printf("\n%d %d %d %d",e++,e++,++e,e++);		//有些东西还不能解释    网上查出来  不同编译器  得出来的答案不一样 
    int i = 3;
 printf("\n%d,%d,%d,%d,%d\n",i++,++i,i,i++,i);
 printf("%d\n",i);
    return 0;
}
