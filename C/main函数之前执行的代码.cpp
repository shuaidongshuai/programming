#include <stdio.h>
#include <stdlib.h>
void init(void) __attribute__((constructor));

void init(void){

    printf("before enter main!\n");

}

void exit_func(void){

    printf("after leave main!\n");

}

int main(void){

    int *m = (int *)malloc(sizeof(int));

    atexit(exit_func);

    printf("hello world!\n");

}
/*
全局变量构造，如各个全局类对象的构造函数调用  和  标记 __attribute__((constructor))属性的各个函数。
它们都应该在进入main前进行调用。
*/ 
