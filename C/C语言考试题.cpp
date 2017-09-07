#include<stdio.h>
#define len sizeof(struct student)
struct student{
	int age;
	char name[20];
	char sex[4];
};
int main()
{
	struct student std[3] ;
	for(int i = 0;i<3;i++)
	{
		scanf("%d",&std[i].age);
		scanf("%s",std[i].name);
		getchar();
		scanf("%s",std[i].sex);	
	}
	struct student *p = std;
	for(int i = 0;i<3;i++)
	{
		printf("%s",p[i]->name);
	}
}
