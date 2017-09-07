/*
* File Name: add_sub.c
*
* Descriptions: 
*		Test the add and sub.
*
* Author: 
*		Zheng Qiang
* Kernel Version: 2.6.29
*
* Update:
* 		-	2009.12.20	Zheng Qiang	 Creat this file
*/
#include <linux/init.h>
#include <linux/module.h>
#include "add_sub.h"

int add_integer(int a, int b)
{
        return a+b;
}

int sub_integer(int a, int b)
{
        return a-b;
}

EXPORT_SYMBOL(add_integer);
EXPORT_SYMBOL(sub_integer);
MODULE_LICENSE("Dual BSD/GPL");