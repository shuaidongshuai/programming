#include<stdio.h>
void hell(void)
{
	printf("Hello,word!\n");
 } 
 void three(void)
 {
 	int i;
 	for(i=0;i<3;i++)
 	hell();
 }
 int main()
 {
 	three();
 }
