#include <stdio.h>
#include <string.h>

int test1()
{
    char s[] = "456789";
    char d[] = "12";
    strcpy(d,s);
    printf("sizeof(d):%d\n",sizeof(d));
    printf ("%s\n%s\n",d,s);
    printf("sizeof(d):%d\n",sizeof(d));
    for(int i = 0;i < 5;++i)
    	printf("%c ",d[i]);
    return 0;
}
/*
sizeof(d):3
456789
456789
sizeof(d):3
4 5 6 7 8

strcpy将源字符串拷贝到目标字符串时，并不检查目标字符串的长度，如果源字符串过长会导致目标内存后面的空间被覆盖
*/

int test2()
{
    char s[] = "456789";
    char d[] = "12";
    strncpy(d,s,4);
    printf("sizeof(d):%d\n",sizeof(d));
    printf ("%s\n%s\n",d,s);
    printf("sizeof(d):%d\n",sizeof(d));
    for(int i = 0;i < 5;++i)
    	printf("%c ",d[i]);
    return 0;
}

int main()
{
	test2();
}
