#include"../include/student.h"


//创建学生信息库，返回信息库的地址
Linklist creat(void)
{
Linklist L=NULL;
Student *s,*p;
char a='a';
s=(Student *)malloc(sizeof(Student));
s->prior=NULL;
s->next=NULL;
L=s;
p=s;
printf("开始创建学生信息\n");
while(a!='0')
  {s=(Student *)malloc(sizeof(Student));
   if(s!=NULL)
   {s->prior=p;
	p->next=s;
	s->next=NULL;
	p=s;
	input(s);                  //录入学生信息
	rank_score(s);            //计算该学生的成绩排名
	printf("是否继续添加学生信息?(按任意键继续,0结束)\n");
   }
   else 
      {printf("分配内存失败");
	   break;}
  a=getchar();
  }
  printf("创建学生信息完成,再见!!\n");
return L;
}

//输入一个学生的信息
void input(Student *p)
 {char temp[20];
  gets(temp);
 int number;
 printf("开始录入:\n");
 printf("请输入学号:");
 scanf("%d",&(p->Person.number));
 gets(temp);
 while(repeat_number(p,p->Person.number)==1) //判断学号是否重复
    {printf("输入的学号已存在,请重新输入\n");
     printf("请输入学号:");
     scanf("%d",&(p->Person.number));
	 gets(temp);
    }
 printf("请输入姓名:");
 scanf("%s",p->Person.name);
 gets(temp);
/* printf("请输入密码:");
 scanf("%s",p->Person.password);
 gets(temp);*/
 strcpy(p->Person.password,"123");
 printf("请输入年龄:");
 scanf("%d",&(p->Person.age));
 gets(temp);
 printf("请输入班级:");
 scanf("%d",&(p->Person.class));
 gets(temp);
 printf("请输入数学成绩:");
 scanf("%d",&(p->Study.math));
 gets(temp);
 printf("请输入C语言成绩:");
 scanf("%d",&(p->Study.c_language));
 gets(temp);
 printf("请输入语文成绩:");
 scanf("%d",&(p->Study.chinese));
 printf("录入结束\n");
 gets(temp);
 }

//查询学号是否重复，重复学号返回1，否则返回0
int repeat_number(const Student *s,int n)
{s=s->prior;
while(s!=NULL)
  {if(s->Person.number==n)
		return 1;
    else s=s->prior;
  }
return 0;
}

//按学号查找学生，返回该学生指针，否则返回NULL
Student *search_number(const Linklist L,int n)
{
Student *s;
s=L;
while(s!=NULL)
 {
  if(s->Person.number==n)
	  return s;
  else s=s->next;
 }
return s;
}

//根据姓名查询，返回该学生的指针，否则返回NULL
Student *search_name(const Linklist L,char na[])
 {
 Student *s;
 s=L;
 while(s!=NULL)
   {
   if(strcmp(s->Person.name,na)==0)
     return s;
   else s=s->next;
   }
 return s;
 }

//根据班级群体查找，返回该班级学生的指针数组的首地址，以NULL结束
Student **search_class(const Linklist L,int clas)
 {
 static Student *cla[100];
 Student *s;
 int i=0;
 s=L;
 while(s!=NULL)
  {
    if(s->Person.class==clas)
		cla[i++]=s;
    s=s->next;
  }
 cla[i]=NULL;
 return cla;
 }


//显示一个学生的信息
void display(const Student *s)
 {
  printf("==========================================================\n");
  printf("|学号| 姓名 |年龄|班级|数学成绩|C语言成绩|语文成绩|名次|\n");
  printf("|%4d|%8s|%4d|%4d|%8d|%9d|%8d|%4d|\n",
		  s->Person.number,s->Person.name,s->Person.age,s->Person.class,s->Study.math,s->Study.c_language,s->Study.chinese,s->Study.rank);
  printf("==========================================================\n");
 }


//删除链表L中的学生的信息
void delete_stu(Linklist L)
{int num;
 char a,f='a',temp[5];
 Student *s;
while(f!='q'&&f!='Q')
  {
   printf("请输入要删除学生的学号:");
   scanf("%d",&num);
   s=search_number(L,num);
   gets(temp);
   if(s==NULL)
	 printf("**对不起,不存在该学生信息**\n");
   else
     {display(s);
      printf("**确定要删除此学生的信息吗?(Y/N)**");
      a=getchar();
      if(a=='Y')
       { if(s->next==NULL)
		   s->prior->next=s->next;
		 else
		 {s->prior->next=s->next;
          s->next->prior=s->prior;
		   }
		 free(s);
	     printf("!!该学生信息已删除\n");
                }
            }
   gets(temp);
   printf("**按Q退出,按其他键继续删除**\n");
   f=getchar();
  }
return;
}

//计算某学生总成绩名次
void rank_score(Student *s)
{
int s_score=s->Study.math+s->Study.c_language+s->Study.chinese;
int p_score;
Student *p;
s->Study.rank=1;
p=s->prior;
while(p->prior!=NULL)
  {
  p_score=p->Study.math+p->Study.c_language+p->Study.chinese;
  if(s_score<p_score)
	  s->Study.rank++;
  else if(s_score>p_score)
	  p->Study.rank++;
  p=p->prior;
  }
return;
}


//按学号对学生顺序排序
void sort_number(Linklist L)
{
Student *s,*r,min;
s=L->next;

while(s->next!=NULL)
   {r=s->next;
    while(r!=NULL)
	  {if(r->Person.number<s->Person.number)
		  { min.Person=r->Person;
			min.Study=r->Study;
		    r->Person=s->Person;
			r->Study=s->Study;
		    s->Study=min.Study;
			s->Person=min.Person;
		  }
	   r=r->next;
      }
	s=s->next;
   }
}



//根据学生名次顺序排序
void sort_rank(Linklist L)
{
Student *s,*r,min;
s=L->next;
while(s->next!=NULL)
  {
   r=s->next;
   while(r!=NULL)
     {
	  if(r->Study.rank<s->Study.rank)
	    {
		  min.Person=r->Person;
		  min.Study=r->Study;
		  r->Person=s->Person;
		  r->Study=s->Study;
		  s->Person=min.Person;
		  s->Study=min.Study;
		}
	  r=r->next;
	 }
   s=s->next;
  }
}


//显示所有学生信息列表
void display_all(const Linklist L)
{
 Student *s;
 s=L->next;
 while(s!=NULL)
  {  display(s);
     s=s->next;
  }
}

//根据数学成绩排序
void sort_math(Linklist L)
{
Student *s,*r,max;
s=L->next;
while(s->next!=NULL)
   {
    r=s->next;
	while(r!=NULL)
     {
	   if(r->Study.math>s->Study.math)
	     {
	       max.Person=r->Person;
		   max.Study=r->Study;
		   r->Person=s->Person;
	       r->Study=s->Study;
	       s->Person=max.Person;
		   s->Study=max.Study;
	     }
	    r=r->next;
     }
    s=s->next;
   }
}


//根据c语言成绩排序
void sort_c_language(Linklist L)
{
Student *s,*r,max;
s=L->next;
while(s->next!=NULL)
   {
    r=s->next;
	while(r!=NULL)
     {
	   if(r->Study.c_language>s->Study.c_language)
	     {
	       max.Person=r->Person;
		   max.Study=r->Study;
		   r->Person=s->Person;
	       r->Study=s->Study;
	       s->Person=max.Person;
		   s->Study=max.Study;
	     }
	    r=r->next;
     }
    s=s->next;
   }
}


//根据语文成绩排序
void sort_chinese(Linklist L)
{
Student *s,*r,max;
s=L->next;
while(s->next!=NULL)
   {
    r=s->next;
	while(r!=NULL)
     {
	   if(r->Study.chinese>s->Study.chinese)
	     {
	       max.Person=r->Person;
		   max.Study=r->Study;
		   r->Person=s->Person;
	       r->Study=s->Study;
	       s->Person=max.Person;
		   s->Study=max.Study;
	     }
	    r=r->next;
     }
    s=s->next;
   }
}



//保存链表数据到文件
void save(const Linklist L)
{
  FILE *fp;
  int i;
  Student *s;
  s=L->next;
  if((fp=fopen("./dat/student.dat","w"))==NULL)
       {
       printf("cannot open the file\n");
       exit(0);
       }
   while(s!=NULL)
           {
		if(fwrite(s,sizeof(Student),1,fp)!=1)
       printf("file write error\n");   
       s=s->next; 
          }
   fclose(fp);
   printf("****保存成功!****\n");
}

//从文件中读取数据并建立链表，返回链表头指针
Linklist read(void)
{ FILE *fp;
Linklist L=NULL;
Student *s,*r;
s=(Student *)malloc(sizeof(Student));
s->prior=NULL;s->next=NULL;
L=s;r=s;
if((fp=fopen("./dat/student.dat","r"))==NULL)
    {
    printf("学生信息数据库错误,请与管理员联系\n");
    exit(0);
    }
while(!feof(fp))
       {
      s=(Student *)malloc(sizeof(Student));
      if(s!=NULL)
      		{fread(s,sizeof(Student),1,fp);
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
 return L;
}
