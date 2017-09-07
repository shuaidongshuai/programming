
#include<stdio.h>
int main()
{
	char a; 
	printf("**************咱们来玩21根火柴的益智小游戏*****************\t\t\t\t\t\t\t\t\t\t\t\n");
	printf("****************玩赢东哥，东哥给你洗袜子******************\t\t\t\t\t\t\t\t\t\t\t\n");
	printf("****************每人一次只能拿1到4根火柴******************\t\t\t\t\t\t\t\t\t\t\t\n");
	printf("注意！游戏开始了······\n");
	int sheng=21,you,me;
	while(1)
	{
	printf("****************火柴还剩下%d根****************************\t\t\t\t\t\t\t\t\t\t\t\n",sheng);
	printf("****************请输入你要拿取得火柴数：******************\t\t\t\t\t\t\t\t\t\t\t\n");
	printf("请输入：");
	scanf("%d",&you);
	if(you<1||you>4||you>sheng)
	{
	printf("****************呵呵，小样还敢犯规************************\t\t\t\t\t\t\t\t\t\t\t\n");
	continue;
	 } 
	 me=5-you;
	 sheng=sheng-you-me; 
	 printf("***************我拿了%d的火柴****************************\t\t\t\t\t\t\t\t\t\t\t\n",me);
	 if(sheng==1)
	 {
	 		printf("****************不好意思你输了！！！**********************\t\t\t\t\t\t\t\t\t\t\t\n");
	 			a=getchar(); 
	 			printf("按回车键结束\n");
	a=getchar();
	break;
}
 } 
}
