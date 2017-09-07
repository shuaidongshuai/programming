#include"../include/student.h"
#include"../include/teacher.h"
#include"../include/admin.h"


//删除教师信息
void delete_te(Link H)
{
int num;
char a,f='a',temp[10];
Teacher *s;
while(f!='q'&&f!='Q')
  {
   printf("请输入要删除教师的编号:");
   scanf("%d",&num);gets(temp);
   s=search_te(H,num);
   if(s==NULL)
	   printf("**对不起,不存在该教师信息**\n");
   else
      {display_te(s);
	   printf("确定要删除此教师的信息吗? (Y/N)");
	   a=getchar();
	   if(a=='Y')
	           {
		  if(s->next==NULL)
			  s->prior->next=s->next;
		  else
		    {s->prior->next=s->next;
		     s->next->prior=s->prior;
			}
		  free(s);
		 printf("该教师信息已删除\n");
		 gets(temp);
		 }
	   else gets(temp);
	      }
	 //  gets(temp);
   printf("**按Q键退出,按其他键继续删除**\n");
   f=getchar();
  }
return;
}

//添加教师信息
void insert_te(Link H)
{
 Teacher *s,*r;
 char temp[10];
 r=H;
 while(1)
 {
  while(r->next!=NULL)
    	 r=r->next;
  s=(Teacher *)malloc(sizeof(Teacher));
   if(s!=NULL)
    {printf("按任意键开始添加\n");
	 s->prior=r;
	 s->next=NULL;
	 r->next=s;
	 input_te(s);
    printf("添加教师信息成功\n");
	}
   else 
   printf("!!创建失败!!\n");
   //gets(temp);
   printf("是否继续添加教师信息?(Y/N)");
   if(getchar()=='Y')
       continue;
   else
	   return;
  }
}

//添加学生信息
void insert_stu(Linklist L)
{
 Student *s,*r;
 char temp[10];
 r=L;
 while(1)
 {
  while(r->next!=NULL)
    	 r=r->next;
  s=(Student *)malloc(sizeof(Student));
   if(s!=NULL)
    {printf("按任意键开始添加\n");
	 s->prior=r;
	 s->next=NULL;
	 r->next=s;
	 input(s);
    printf("添加学生信息成功\n");
	}
   else 
   printf("!!创建失败!!\n");
   //gets(temp);
   printf("是否继续添加学生信息?(Y/N)");
   if(getchar()=='Y')
       continue;
   else
	   return;
  }
}

//根据教师姓名查询，返回该教师的指针，否则返回NULL
Teacher *search_tename(const Link H,char na[])
{Teacher *s=H;
while(s!=NULL)
  {
   if(strcmp(s->te_name,na)==0)
  		return s;
  	else s=s->next;
   }
return s;
 }

//根据姓名显示教师信息
void display_tename(const Link H)
{
 Teacher *s;
 char na[128];
 printf("请输入要查看的教师的姓名:");
 scanf("%s",na);
 s=search_tename(H,na);
 if(s!=NULL)
 	display_te(s);
 else
 	printf("您输入的教师名字不存在\n");
 return;
}

//根据教师编号显示教师信息
void display_tenum(const Link H)
{
Teacher *s;
int num;
printf("请输入要查看的教师编号:");
scanf("%d",&num);
s=search_te(H,num);
if(s!=NULL)
 	display_te(s);
else
 	printf("您输入的教师编号不存在\n");
return;
}


//显示所有教师信息
void display_allte(const Link H)
{Teacher *s;
s=H->next;
while(s!=NULL)
	{
      display_te(s);
      s=s->next;
	}
return;
}
