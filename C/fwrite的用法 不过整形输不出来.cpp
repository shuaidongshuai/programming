#include<stdio.h> 
#include<stdlib.h>
struct student
{
	char name[8];
	char sex[8];
	int age;
}st[2];
int main()
{
	int i;
	FILE *p;
	p=fopen("student.txt","a");
	if(p==NULL) printf("can't open");
	for(i=0;i<2;i++)
	{
		scanf("%s%s%d",st[i].name,st[i].sex,&st[i].age);
		fwrite(&st[i],sizeof(student),1,p);
	}
	fclose(p);
 } 
