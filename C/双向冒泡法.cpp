#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define MAX 30
#define SWAP(x, y) {int t; t = x; x = y; y = t;}
 
void Shakersort(int []);
 
int main()
{
    int i;
    int number[MAX];
 
    srand(time(NULL));
    printf("排序前：");
    for (i = 0; i < MAX; i++)
    {
        number[i] = rand() % 100;
        printf("%d ", number[i]);
    }
     
    Shakersort(number);
    printf("\n改进冒泡排序后：");
    for (i = 0; i < MAX; i++)
        printf("%d ", number[i]);
    printf("\n");
 
    return 0;
}
 
void Shakersort(int number[])
{
    int left = 0, right = MAX - 1, shift = 1;
    int i;
     
    while (left < right)
    {
        for (i = left; i < right; i++)
        {
            if (number[i] > number[i+1])
            {
                SWAP(number[i], number[i+1])
                shift = i;
            }
        }
        right = shift;
        for (i = right-1; i >= left; i--)
        {
            if (number[i] > number[i+1])
            {
                SWAP(number[i], number[i+1])
                shift = i + 1;
            }
        }
        left = shift;
    }
}
