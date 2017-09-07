#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main()
{
	char q[10];
	printf("请输入你姓什么（按回车键结束）：");
	scanf("%s",q);
	printf("请允许我给你儿子随机取个名字\n"); 
	char **p;
	p=(char **)malloc(25*sizeof(char *));
	for(int b=0;b<25;b++)
	*(p+b)=(char *)malloc(6*sizeof(char));
	strcpy(p[0],"三");
	strcpy(p[1],"龙");
	strcpy(p[2],"天");
	strcpy(p[3],"阳");
	strcpy(p[4],"东");
	strcpy(p[5],"牛");
	strcpy(p[6],"强");
	strcpy(p[7],"帅");
	strcpy(p[8],"伟");
	strcpy(p[9],"舞");
	strcpy(p[10],"横");
	strcpy(p[11],"鬼");
	strcpy(p[12],"桂");
	strcpy(p[13],"浩");
	strcpy(p[14],"爽");
	strcpy(p[15],"龍");
	strcpy(p[16],"安");
	strcpy(p[17],"运");
	strcpy(p[18],"雷");
	strcpy(p[19],"欧");
	strcpy(p[20],"阳");
	strcpy(p[21],"修");
	strcpy(p[22],"跑");
	strcpy(p[23],"恒");
	strcpy(p[24],"瑶");
	srand(time(0));
	int a=rand()%2;
		printf("%s",q); 
	for(int i=0;i<=a;i++)
	{
	int j=rand()%18+1;
	printf("%s",p[j]);
    };
    printf("\n");
    system("pause"); 
 } 
