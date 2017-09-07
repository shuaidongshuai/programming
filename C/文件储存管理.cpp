#include<stdio.h>
typedef struct student
{
	char name[20];
	int chinese;
	int math;
	int english;
}str;
str a[100];
int i=0;
void out()//从文件中读出数据 
{
	FILE *fp;
	fp=fopen("D:\\dong.dat","a+");
	int j=0;
	while(fread(&a[j],sizeof(str),1,fp)==1)		//  返回值就是fread的count值    fread(buffer,size,cout,fp) 
	{
		printf("姓名：%s\n",a[j].name);
		printf("语文成绩：%d\n",a[j].chinese);
		printf("数学成绩：%d\n",a[j].math);
		printf("外语成绩：%d\n",a[j].english);
		j++;
		printf("\n");
	}
	fclose(fp);
}
void save()//保存进文件 
{
	FILE *fp;
	fp=fopen("D:\\dong.dat","w+");
	int j=0;
	
	//这不能像上面 while(fread(&a[j],sizeof(str),1,fp)==1)这样，，因为a[100]是全局变量 int 都==0  都是初始化了的   他会一直写如文件fwrite返回值一直为1 
	for(j;j<=i;j++)
	fwrite(&a[j],sizeof(str),1,fp);

	fclose(fp);
}
int main()
{
	int j,n;
	out();
	printf("请问要输入几组数据：");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
	printf("请输入姓名：");
	scanf("%s", a[i].name);
	printf("请输入语文成绩：");
	scanf("%d", &a[i].chinese);
	printf("请输入数学成绩：");
	scanf("%d", &a[i].math);
	printf("请输入外语成绩：");
	scanf("%d", &a[i].english);		
	}
	save();
 } 
