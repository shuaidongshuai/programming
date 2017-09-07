#include"../include/student.h"
#include"../include/teacher.h"



//创建教师信息库
Link creat_te(void)
{
Link H=NULL;
Teacher *s,*p;
char a='a';
s=(Teacher *)malloc(sizeof(Teacher));
s->prior=NULL;
s->next=NULL;
H=s;
p=s;
printf("开始创建教师信息\n");
while(a!='0')
  {s=(Teacher *)malloc(sizeof(Teacher));
   if(s!=NULL)
   {  s->prior=p;
      s->next=NULL;
	  p->next=s;
	  p=s;
	  input_te(s);
	  printf("是否继续添加教师信息?(任意键继续,0结束)\n");
   }
   else
   {printf("分配内存失败\n");
	   break;}
   a=getchar();
  }
printf("创建教师信息完成,再见!!\n");
return H;
}

//录入一个教师的信息
void input_te(Teacher *s)
{
 char temp[20];
 gets(temp);
 int number;
 printf("开始录入数据:\n");
 printf("请输入教师编号:");
 scanf("%d",&(s->te_number));
 gets(temp);
 while(repeat_num(s,s->te_number)==1)
    {printf("输入的编号已存在,请重新输入\n");
	 printf("请输入编号:");
	 scanf("%d",&(s->te_number));
	     gets(temp);
	}
 printf("请输入教师姓名:");
 scanf("%s",s->te_name);
 gets(temp);
/* printf("请输入密码:");
 scanf("%s",s->te_password);
 gets(temp);*/
 strcpy(s->te_password,"1234");
 printf("请输入所属班级:");
 scanf("%d",&(s->te_class));
 printf("录入结束\n");
 gets(temp);
}

//查询教师编号是否重复，重复返回1，否则返回0
int repeat_num(const Teacher *s,int n)
{s=s->prior;
 while(s!=NULL)
   {
    if(s->te_number==n)
		 return 1;
	else s=s->prior;
   }
 return 0;
}

//根据教师编号查询，返回教师的指针，否则返回NULL
Teacher *search_te(const Link H,int n)
{Teacher *s;
 s=H->next;
 while(s!=NULL)
    {
	 if(s->te_number==n)
		 return s;
	 else s=s->next;
	}
return s;
}

//显示一个教师的信息
void display_te(const Teacher *s)
 {
  printf("==================\n");
  printf("|编号| 姓名 |班级|\n");
  printf("|%4d|%8s|%4d|\n",s->te_number,s->te_name,s->te_class);
  printf("==================\n");
 }

//保存链表数据到文件
void save_te(const Link H)
{
  FILE *fp;
  int i;
  Teacher *s;
  s=H->next;
  if((fp=fopen("./dat/teacher.dat","w"))==NULL)
       {
       printf("cannot open the file\n");
       exit(0);
       }
   while(s!=NULL)
           {
		if(fwrite(s,sizeof(Teacher),1,fp)!=1)
       printf("file write error\n");   
       s=s->next; 
          }
   fclose(fp);
   printf("****保存成功!****\n");
}

//从文件中读取数据并建立链表，返回链表头指针
Link read_te(void)
{ FILE *fp;
Link H=NULL;
Teacher *s,*r;
s=(Teacher *)malloc(sizeof(Teacher));
s->prior=NULL;s->next=NULL;
H=s;r=s;
if((fp=fopen("./dat/teacher.dat","r"))==NULL)
    {
    printf("教师信息数据库错误,请与管理员联系\n");
    exit(0);
    }
while(!feof(fp))
       {
      s=(Teacher *)malloc(sizeof(Teacher));
      if(s!=NULL)
      		{fread(s,sizeof(Teacher),1,fp);
      		s->prior=r;
      		r->next=s;
      		s->next=NULL;
      		r=s;      		
      		}
       else break;
       }
 fclose(fp);
 s->prior->next=NULL;
 free(s);
 return H;
}

//根据学号查看一个学生信息
void display_number(const Linklist L)
{Student *s;
 int num;
 printf("请输入要查看的学生的学号:");
 scanf("%d",&num);
 s=search_number(L,num);
 if(s!=NULL)
	display(s);
 else
	printf("您输入的学生学号不存在\n");
 return;
}

//根据姓名查看学生信息；
void display_name(const Linklist L)
{
Student *s;
char na[128];
printf("请输入要查看的学生的姓名:");
scanf("%s",na);
s=search_name(L,na);
if(s!=NULL)
	display(s);
else
	printf("您输入的学生姓名不存在\n");
return;
}

//根据班级显示该班级所有的学生信息
void display_class(const Linklist L)
{
  Student **s;
  int cla;
  printf("请输入要查看的班级:");
  scanf("%d",&cla);
  s=search_class(L,cla);
  if((*s)==NULL)
  	printf("您选择的班级不存在\n");
  while((*s)!=NULL)
	{
		display(*s);			
		s++;
	}
return;
}


//根据新的成绩计算所有学生的名次
void rank_new(Linklist L)
{
 Student *s;
 s=L->next;
 while(s!=NULL)
  {rank_score(s);
   s=s->next;  
  }
}
