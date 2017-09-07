#include<stdio.h>
int main()
{
	char grade;
	int score;
	scanf("%d",&score);
	grade=(score>=90?'A':6(score>=60?'B':'C'));
	printf("%d belong to %c",score,grade);
}
