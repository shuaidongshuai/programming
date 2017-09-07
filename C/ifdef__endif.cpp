#include <stdio.h>
#define dong printf("nice to see you\n")
/* 判断申明 */
#ifdef DEBUG_PRINT					//如果之前被定义了 
#define MyPrint printf("hello\n")	// 那么 
#else								// 没有定义 
#define MyPrint					// 则 定义为空 
#endif
#ifdef dong					//如果之前被定义了 
#define dong printf("dong\n")	// 那么 
#endif

// main函数
int main()
{
MyPrint;
dong;
return 0;
}
