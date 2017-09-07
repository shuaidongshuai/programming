#include<iostream>
using namespace std;
#include <stdio.h>
#include <string>

int main()
{
	char e;
	while(e!=EOF)
	{
		e = getchar();
		cout<<e;
	}
	cout<<"dong";
 }
int  main2()
{
    int ch;
    do{
        ch=getchar();
        printf("ch=%d\n", ch ); //输出读返回的ch值，读到EOF会输出-1
    } while ( ch!=EOF );
}
int main3()
{
	int a[10];
	while(scanf("%d",a)!=EOF)
	{
		printf("a = %d\n",a);
	}
}
int main4()
{
	cout<<EOF<<endl;
 } 
/*
EOF 是个宏，其意思是：End Of File，文件尾标志。 从数值上来看，就是整数-1
在C语言的头文件中对其进行了宏定义：
stdio.h:    # define EOF (-1)
当读文件操作时，遇到文件结束位置或读数据出错均会返回 EOF。 （C语言中所有的输入输出操作均是按读文件的思想来设计的，
或者说，是文件操作的一种特例，如getchar（）就是fgetc(stdin) 的一个宏 ）
int getchar() ; //从标准输入缓冲区读取一个字符，成功返回该字符的ASCII值，出错，返回EOF
那么，如何在键盘输入时，产生EOF呢？ 不同的系统方法不同：
linux系统下，在输入回车换行后的空行位置，按 ctrl+d (先按ctrl键，不放，再按d键）
windows系统下，在输入回车换行后的空行位置，按 ctrl+z，再回车确认
以下代码供参考：
#include <stdio.h>
void main()
{
    int ch;
    do {
        ch=getchar();
        printf("ch=%d\n", ch ); //输出读返回的ch值，读到EOF会输出-1
    } while ( ch!=EOF );
}
*/
