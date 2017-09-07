#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
typedef struct student
{
	char name[20];
	int chinese;
	int math;
	int english;
}str;
int i = 0;
str a[100];
int input()
{
	for (i = 0; i <= 100; i++)
	{
		printf("请输入姓名：");
		scanf_s("%s", a[i].name, sizeof(a[i].name));
		printf("请输入语文成绩：");
		scanf_s("%d", &a[i].chinese);
		printf("请输入数学成绩：");
		scanf_s("%d", &a[i].math);
		printf("请输入外语成绩：");
		scanf_s("%d", &a[i].english);
		char b[20];
		getchar();
		while (1)
		{
			printf("dong是否还想输入  y/n\n");
			scanf_s("%s", &b, sizeof(b));
			getchar();
			if (!strcmp(b, "y") || !strcmp(b, "Y"))
				break;
			else if (!strcmp(b, "n") || !strcmp(b, "N"))
				return i;
			else
			{
				continue;
			}
		}
	}
	return i;
}
void output()
{
	if (i != 0)
	{
		for (int j = 0; j <=i; j++)
		{
			printf("%d-------------\n", j + 1);
			printf("姓名：%s\n", a[j].name);
			printf("语文：%d\n数学：%d\n外语：%d\n\n", a[j].chinese, a[j].math, a[j].english);
		}
	}
	else
		printf("还没有数据\n\n");
}
void chazhao(char c[20])
{
	int j;
	for (j = 0; j <=i; j++)
	{
		if (!strcmp(a[j].name, c))
		{
			printf("%d-------------\n",j+1);
			printf("姓名：%s\n", a[j].name);
			printf("语文：%d\n数学：%d\n外语：%d\n", a[j].chinese, a[j].math, a[j].english);
			break;
		}
	}
	if (j - 1 == i)
	{
		printf("没有这个人\n\n");
	}
}
void charu()
{
	int b,c;
	printf("要插入到第几个：");
	scanf_s("%d", &b, sizeof(int));
	for (c=i; b-1 <=c; c--)
	{
		strcpy(a[c + 1].name, a[c].name);
		a[c + 1].chinese = a[c].chinese;
		a[c + 1].math = a[c].math;
		a[c + 1].english = a[c].english;
	}
	i++;
	printf("请输入学生信息：\n");
	printf("请输入姓名：");
	scanf_s("%s", a[b-1].name, sizeof(a[b].name));
	printf("请输入语文成绩：");
	scanf_s("%d", &a[b-1].chinese);
	printf("请输入数学成绩：");
	scanf_s("%d", &a[b-1].math);
	printf("请输入外语成绩：");
	scanf_s("%d", &a[b-1].english);
}
void shanchu()
{
	int c;
	printf("要删除第几个：");
	scanf_s("%d", &c, sizeof(int));
	for (c = c - 1; c < i;c++)
	{
		strcpy(a[c].name, a[c+1].name);
		a[c].chinese = a[c+1].chinese;
		a[c].math = a[c+1].math;
		a[c].english = a[c+1].english;
	}
	i--;
}
char* xingming()
{
		char **p;
		char xingming[20];
		xingming[0] = '\0';
		p = (char **)malloc(19 * sizeof(char *));
		for (int b = 0; b<19; b++)
			*(p + b) = (char *)malloc(6 * sizeof(char));
		strcpy(p[0], "明");
		strcpy(p[1], "龙");
		strcpy(p[2], "天");
		strcpy(p[3], "阳");
		strcpy(p[4], "东");
		strcpy(p[5], "牛");
		strcpy(p[6], "强");
		strcpy(p[7], "帅");
		strcpy(p[8], "伟");
		strcpy(p[9], "舞");
		strcpy(p[10], "横");
		strcpy(p[11], "鬼");
		strcpy(p[12], "桂");
		strcpy(p[13], "浩");
		strcpy(p[14], "爽");
		strcpy(p[15], "龍");
		strcpy(p[16], "伊");
		strcpy(p[17], "运");
		strcpy(p[18], "雷");
		srand(time(0));
		int c = rand() % 2+1;
		for (int d = 0; d <= c; d++)
		{
			int j = rand() % 18 + 1;
			strcat(xingming, p[j]);
		};
			return xingming;
}
void yuanshi()
{
	int b;
	srand(time(0));
	for (i = 0; i < 10; i++)
	{
		strcpy(a[i].name, xingming());
		b = rand() % 10+ 1;
		a[i].chinese = b;
		Sleep(350);
		printf(".");
		b = rand() % 100 + 1;
		a[i].math = b;
		Sleep(350);
		printf(".");
		b = rand() % 100 + 1;
		a[i].english = b;
		Sleep(350);
		printf(".");
	}
	i--;
	printf("\n");
}
int main()
{
	int n;
	char name[20];
	while (1)
	{
		printf("1-重新输入成绩\t2-输出所有成绩\t3-查找\t4-插入\t5-自动生成(需要11秒)\t6-删除\t\t9-退出\t\t（请不要乱按）\n");
		scanf_s("%d", &n, 4);
		if (n == 1)
			int i = input();
		if (2 == n)
			output();
		if (3 == n)
		{
			printf("请输入要查找的人：");
			scanf("%s", name, sizeof(name));
			chazhao(name);
		}
		if (4 == n)
		{
			charu();
		}
		if (5 == n)
		{
			yuanshi();
		}
		if (6 == n)
		{
			shanchu();
		}
		if (9 == n)
			break;
	}
	system("pause");
	return 0;
}
