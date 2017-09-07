#include"../include/student.h"
#include"../include/teacher.h"
#include"../include/admin.h"
#include"../include/menu.h"


char manager[]="admin";
char man_pass[]="admin";

//登录总菜单
void menu(void)
{
int code,status,i;
char temp[10];
Linklist L;
Link H;
while(1)
{
printf("************************************************************\n");
printf("                ****欢迎来到学生管理系统****                 \n");
printf("                       请选择登录权限                       \n" );
printf("                        1) 学生登录                         \n");
printf("                        2) 教师登录                         \n");
printf("                        3) 管理员登录                       \n");
printf("                        4) 离开系统                         \n");
printf("************************************************************\n");
printf("请选择您的操作: ");
while((status=scanf("%d",&code))!=1||code<1||code>4)
    {if(status!=1)
	   scanf("%*s");
	 printf("请重新选择,输入数字1－4\n");
	 printf("请选择您的操作: ");
     	}
gets(temp);
switch(code)
	{
	 case 1:L=read();
			i=load_stu(L);
			if(i!=0)
				{menu_stu(L,i);
				break;}
			else 
      			{printf("Sorry,您输入密码错误次数过多!\n");
				return;}
			break;
	 case 2:H=read_te();
			L=read();
			i=load_te(H);
			if(i!=0)
				{menu_tea(H,L,i);
				break;}
			else
				{printf("Sorry,您输入密码错误次数过多!\n");
				return;}
			break;
	 case 3:i=load_manager();
			if(i==1)
				{menu_admin();
				break;}
			else
				break;
	 case 4:printf("************欢迎再次登录,再见!************\n");
			return;
	}
  }
}

//学生登录功能
int load_stu(Linklist L)
{
int num,i=0;
char pass[32];
Student *s;
while(i<3)
{
printf("*******************************\n");
printf("请输入学号:");
scanf("%d",&num);
printf("请输入密码:");
scanf("%s",pass);
printf("*******************************\n");
s=search_number(L,num);
if(s==NULL)
	{
	printf("您输入的学号有误!\n");
	i++;
	}
else if(strcmp(pass,s->Person.password)!=0)
	   {printf("密码输入错误\n");
 	     i++;   
	       }
    else return num;
    }
return 0;
}


//教师登录功能
int load_te(Link H)
{
int num,i=0;
char pass[32];
Teacher *s;
while(i<3)
{
printf("*******************************\n");
printf("请输入编号:");
scanf("%d",&num);
printf("请输入密码:");
scanf("%s",pass);
printf("*******************************\n");
s=search_te(H,num);
if(s==NULL)
	{printf("您输入的编号有误!\n");
	  i++;}
else if(strcmp(pass,s->te_password)!=0)
	  {printf("密码输入错误\n");
 	  i++;   
	     }
     else return num;
}
return 0;
}

//管理员登录功能
int load_manager(void)
{
char user[32],pass[32];
printf("*******************************\n");
printf("请输入用户名:");
scanf("%s",user);
printf("请输入密码:");
scanf("%s",pass);
printf("*******************************\n");
if(strcmp(user,manager)!=0)
	printf("输入的用户名错误!\n");
else if(strcmp(pass,man_pass)!=0)
	  printf("您输入的密码错误!\n");
else return 1;
return 0;
}



//学生功能菜单
void menu_stu(Linklist L,int number)
{
 int code,status;
 char temp[10];
 Student *s;
 s=search_number(L,number);
 while(1)
 {
 printf("*************************************************\n");
 printf("          ****欢迎%s同学登录****       \n",s->Person.name);
 printf("            1）查看个人基本信息          \n");
 printf("            2) 修改个人基本信息          \n");
 printf("            3)     退出系统              \n");
 printf("*************************************************\n");
 printf("请选择您的操作: ");
 while((status=scanf("%d",&code))!=1||code<1||code>3)
    { if(status!=1)
		 scanf("%*s");
      printf("请输入数字1－3\n");
      printf("请选择您的操作: ");
    }
 gets(temp);
 switch(code)
    {
	 case 1:printf("********************以下是您的个人信息*********************\n");
		    display(s);
			break;
	 case 2:modify_stu(L,s);
	     	break;
	 case 3:printf("您确定要退出?（Y/N）");
			if(getchar()=='Y')
			   {printf("感学您的登录,再见！\n");
			     return;
			       }
			else break;
    }
 }
}



//学生修改个人信息功能菜单
void modify_stu(Linklist L,Student *s)
{int code,status;
char temp[5],F;
while(1)
{            
printf("**************请选择要修改的内容**************\n");
printf("                1) 修改姓名             \n");
printf("                2) 修改密码             \n");
printf("                3) 修改年龄             \n");
printf("                4) 修改班级             \n");
printf("                5) 保存修改             \n");
printf("                6)   返回               \n");
printf("**********************************************\n");
printf("请选择您的操作: ");
while((status=scanf("%d",&code))!=1||code<1||code>6)
   {
     if(status!=1)
		 scanf("%*s");
	 printf("请重新选择数字1－6\n");
	 printf("请选择您的操作: ");
   }
 gets(temp);
switch(code)
  {
   case 1:printf("请输入新的姓名:");
		   scanf("%s",s->Person.name);
		   break;
   case 2:changepass(s);
          break;
   case 3:printf("请输入您的年龄:");
   			scanf("%d",&(s->Person.age));
   			break;
	case 4:printf("请输入您的班级:");
			scanf("%d",&(s->Person.class));
			break;
	case 5:printf("是否保存您的修改?(Y/N)");
  			if(getchar()=='Y')
  				{save(L);break;}
  			else 
  			 break;
    case 6:printf("退出前请确认(Y-保存修改并退出,N-不保存退出,其他键取消)");
  			if((F=getchar())=='Y')
			   {save(L);return;}
			else if(F=='N')
				return;
			else break;
    } 
  }
}

//学生修改密码功能
void changepass(Student *s)
{ char pass[32],passnew[32];
  printf("请输入原始密码:");
  scanf("%s",pass);
    if(strcmp(pass,s->Person.password)!=0)
           {
      printf("密码输入错误\n");
	   }
   else
     { printf("请输入新密码:");
       scanf("%s",pass);
		printf("请再次输入新密码:");
		scanf("%s",passnew);
       if(strcmp(pass,passnew)!=0)
		  printf("两次密码输入不一致\n");
		else 
		  {strcpy(s->Person.password,pass);
		  printf("密码修改成功\n");}
	   }
return;
}



//教师功能菜单
void menu_tea(Link H,Linklist L,int number)
{
 int code,status;
 char temp[10];
 Teacher *s;
 s=search_te(H,number);
 while(1)
 {
  printf("************************************************\n");
  printf("            ****欢迎%s老师登录****            \n",s->te_name);
  printf("              1) 查看个人基本信息        \n");
  printf("              2) 修改个人基本信息         \n");
  printf("              3)   查看学生信息           \n");
  printf("              4)   查看成绩信息           \n");
  printf("              5)   修改学生成绩           \n");
  printf("              6)    退出系统              \n");
  printf("************************************************\n");
printf("请选择您的操作: ");
 while((status=scanf("%d",&code))!=1||code<1||code>6)
     {if(status!=1)
		 scanf("%*s");
	  printf("请重新选择,输入数字1－6\n");
	  printf("请选择您的操作: ");
	 }
  gets(temp);
  switch(code)
     {
	  case 1:printf("*****以下是您的基本信息*****\n");
			 display_te(s);
			 break;
	  case 2:modify_te(H,s);
	         break;
	  case 3:refer_stu(L);
	         break;
	  case 4:refer_study(L);
			 break;
	  case 5:modify_study(L);
			 break;
	  case 6:printf("您确定要退出系统?(Y/N)");
			 if(getchar()=='Y')
			 {printf("****感谢您的登录,再见！****\n");
			   return;}
			 else 
				 break;
	 }
  }
}

//教师修改个人信息功能菜单
void modify_te(Link H,Teacher *s)
{int code,status;
 char temp[10],F;
 while(1)
   {
	 printf("*************请选择要修改的内容**************\n");
	 printf("               1) 修改姓名                  \n");
	 printf("               2) 修改密码                  \n");
	 printf("               3) 修改班级                 \n");
	 printf("               4) 保存修改              \n"); 
	 printf("               5)   返回                    \n");
	 printf("**********************************************\n");
	 printf("请选择您的操作: ");
	 while((status=scanf("%d",&code))!=1||code<1||code>5)
	    {
		 if(status!=1)
			 scanf("%*s");
		 printf("请重新选择,输入数字1－5\n");
		 printf("请选择您的操作: ");
		}
  	gets(temp);
	switch(code)
     	{
		 case 1:printf("请输入新的姓名:");
				scanf("%s",s->te_name);
				break;
		 case 2:changepass_te(s);
				break;
		 case 3:printf("请输入您的班级:");
				scanf("%d",&(s->te_class));
				break;
		 case 4:printf("是否保存您的修改?(Y/N)");
				if(getchar()=='Y')
				 {save_te(H);break;}
				else
				   break;
		 case 5:printf("退出前请确认(Y-保存修改并退出,N-不保存退出,其他键取消)");
  			if((F=getchar())=='Y')
			   {save_te(H);return;}
			else if(F=='N')
				return;
			else break;
	}
   }
 }


//教师修改密码功能
void changepass_te(Teacher *s)
{char pass[32],passnew[32];
 printf("请输入原始密码:");
 scanf("%s",pass);
 if(strcmp(pass,s->te_password)!=0)
	 printf("密码输入错误\n");
 else
   {printf("请输入您的新密码:");
	scanf("%s",pass);
	printf("请再次输入新密码:");
	scanf("%s",passnew);
	if(strcmp(pass,passnew)!=0)
		printf("两次密码输入不一致\n");
	else
	  {strcpy(s->te_password,pass);
	   printf("密码修改成功\n");}
   }
return;
}

//查看学生信息菜单
void refer_stu(Linklist L)
{
int code,status;
char temp[10];
while(1)
{
printf("****************************************************\n");
printf("              1) 按学生学号查询                 \n");
printf("              2) 按学生姓名查询                 \n");
printf("              3) 按班级查看学生信息         \n");
printf("              4) 按学号浏览学生信息         \n");
printf("              5)      返回                        \n");
printf("****************************************************\n");
printf("请选择您的操作: ");
while((status=scanf("%d",&code))!=1||code<1||code>5)
   {if(status!=1)
	   scanf("%*s");
	printf("请重新选择,输入数字1－5\n"); 
	printf("请选择您的操作: ");
   }
gets(temp);
switch(code)
  {
   case 1:display_number(L);
		  break;
   case 2:display_name(L);
		  break;
   case 3:display_class(L);
		  break;
   case 4:sort_number(L);
		  display_all(L);
		  break;
   case 5:printf("您确定要返回? (Y/N) ");
		  if(getchar()=='Y')
		    return;
		  else break;
      }
  }
}

//查看学生成绩功能
void refer_study(Linklist L)
{int code,status;
 char temp[10];
 while(1)
 {
 printf("**************************************************\n");
 printf("              1) 按数学成绩查看                 \n");
 printf("              2) 按C语言成绩查看               \n");
 printf("              3) 按语文成绩查看                 \n");
 printf("              4) 按总成绩名次查看             \n");
 printf("              5)      返回                        \n");
 printf("**************************************************\n");
 printf("请选择您的操作: ");
 while((status=scanf("%d",&code))!=1||code<1||code>5)
   {if(status!=1)
	   scanf("%*s");
	printf("请重新选择,输入数字1－5\n");
	printf("请选择您的操作: ");
   }
 gets(temp);
 switch(code)
   {
     case 1:sort_math(L);
			display_all(L);
			break;
	 case 2:sort_c_language(L);
			display_all(L);
			break;
	 case 3:sort_chinese(L);
			display_all(L);
			break;
	 case 4:sort_rank(L);
			display_all(L);
			break;
	 case 5:printf("您确定要返回? (Y/N) ");
			if(getchar()=='Y')
			  return;
			else break;
   }
 }
}


//教师修改学生成绩功能
void modify_study(Linklist L)
{
	int code,status,number;
	char temp[10],F;
	Student *s;
	printf("请输入要修改学生的学号:");
	scanf("%d",&number);
	s=search_number(L,number);
	if(s==NULL)
	  {printf("您选择的学生不存在\n");
	   return;}
	else
		display(s);
	while(1)
   {
    printf("****************请选择要修改的科目****************\n");
	printf("                1) 修改数学成绩             \n");
	printf("                2) 修改C语言成绩            \n");
	printf("                3) 修改语文成绩              \n");
	printf("                4)   保存修改                    \n");
	printf("                5)    返回                  \n");
	printf("**************************************************\n");
   printf("请选择您的操作: ");
	while((status=scanf("%d",&code))!=1||code<1||code>5) 
    { if(status!=1)
    		scanf("%*s");
      printf("请重新选择,输入数字1－5\n");
      printf("请选择您的操作: ");
    	 }
    gets(temp);
	switch(code)
	    {
	    case 1:printf("请输入新的数学成绩:");
	    		scanf("%d",&(s->Study.math));
	    		break;
	    case 2:printf("请输入新的C语言成绩:");
	    		scanf("%d",&(s->Study.c_language));
	    		break;
	    case 3:printf("请输入新的语文成绩:");
	    		scanf("%d",&(s->Study.chinese));
	    		break;
	    case 4:printf("是否保存您的修改?(Y/N)");
	    		if(getchar()=='Y')
	    		  {rank_new(L);
					save(L);
					break;}
	    		else
	    		  break;
	    case 5:printf("退出前请确认(Y-保存修改并退出,N-不保存退出,其他键取消)");
  				if((F=getchar())=='Y')
			  	 {save(L);return;}
				else if(F=='N')
					return;
				else break;
	    }
    }
}



//管理员功能菜单
void menu_admin(void)
{int code,status;
char temp[10],F;
Linklist L;
Link H;
while(1)
{
printf("***************************************************\n");
printf("             ****欢迎管理人员到来****             \n");
printf("                1) 创建学生信息库             \n");
printf("                2) 创建教师信息库             \n");
printf("                3) 管理学生信息库             \n");
printf("                4) 管理教师信息库				\n");
printf("                5)   退出系统					\n");
printf("***************************************************\n");
printf("请选择您的操作: ");
while((status=scanf("%d",&code))!=1||code<1||code>5)
	{if(status!=1)
		scanf("%*s");
	printf("请重新选择,输入数字1－5\n");
	printf("请选择您的操作: ");
	}
gets(temp);
switch(code)
	{
	 case 1:L=creat();
			save(L);
			break;
	 case 2:H=creat_te();
			save_te(H);
			break;
	 case 3:manage_stu();
			break;
	 case 4:manage_te();
			break;
	 case 5:printf("退出前请确认(Y-保存修改并退出,N-不保存退出,其他键取消)");
	        if((F=getchar())=='Y')
			  {save(L);save_te(H);return;}
			else if(F=='N')
				{printf("您此次修改未保存\n");
				return;}
			else break;
	}
 }
}

//管理学生数据库功能
void manage_stu(void)
{int code,status;
char temp[10],F;
 Linklist L;
 L=read();
 while(1)
 {
 printf("******************************************************\n");
 printf("                  1) 查看学生信息                \n");
 printf("                  2) 修改学生信息                \n");
 printf("                  3) 查看成绩信息                \n");
 printf("                  4) 修改成绩信息		     \n");
 printf("                  5) 添加学生信息                \n");
 printf("                  6) 删除学生信息			\n");
 printf("                  7)   保存修改			\n");
 printf("                  8)     返回			\n");
 printf("******************************************************\n");
 printf("请选择您的操作: ");
 while((status=scanf("%d",&code))!=1||code<1||code>8)
 	{if(status!=1)
		scanf("%*s");
	printf("请重新选择,输入数字1－8\n");
	printf("请选择您的操作: ");
	}
gets(temp);
switch(code)
	{
	 case 1:refer_stu(L);
			break;
	 case 2:modify_stuinfo(L);
			break;
     case 3:refer_study(L);
			break;
	 case 4:modify_study(L);
			break;
	 case 5:insert_stu(L);
	  		break;
	 case 6:delete_stu(L);
			break;
	 case 7:printf("确定保存您此次的修改?(Y/N)");
			if(getchar()=='Y')
				{save(L);break;}
			else 
	          break;
	 case 8:printf("退出请确认(Y-保存并退出,N-不保存退出,其他键取消)");
	 		if((F=getchar())=='Y')
			  {save(L);return;}
	 		else if(F=='N')
				return;
			else break;
	}
 
 }
}

//管理员修改学生个人信息
void modify_stuinfo(Linklist L)
{
 int code,status,number;
 char temp[10],F;
 Student *s;
 printf("请输入要修改的学生学号:");
 scanf("%d",&number);
 s=search_number(L,number);
 if(s==NULL)
 	{printf("您选择的学生不存在\n");
	 return;}
	
while(1)
{display(s);
printf("**************请选择要修改的信息****************\n");
printf("                1) 修改姓名               \n");
printf("                2) 修改密码               \n");
printf("                3) 修改班级               \n");
printf("                4) 修改年龄               \n");
printf("                5) 保存修改               \n");
printf("                6)   返回                 \n");
printf("************************************************\n");
printf("请选择您的操作: ");
while((status=scanf("%d",&code))!=1||code<1||code>6)
	{if(status!=1)
		scanf("%*s");
	printf("请重新选择,输入数字1－6\n");
	printf("请选择您的操作: ");
	}
gets(temp);
switch(code)
	{
	 case 1:printf("请输入新的姓名:");
			scanf("%s",s->Person.name);
			break;
	 case 2:printf("请输入新的密码:");
			scanf("%s",s->Person.password);
			break;
	 case 3:printf("请输入新的班级:");
			scanf("%d",&(s->Person.class));
			break;
	 case 4:printf("请输入新的年龄:");
			scanf("%d",&(s->Person.age));
			break;
	 case 5:printf("确认保存您的修改?(Y/N)");
			if(getchar()=='Y')
			 {save(L);break;}
			else
			  break;
	 case 6:printf("退出请确认(Y-保存修改并退出,N-不保存退出,其他键取消)");
			if((F=getchar())=='Y')
				{save(L);return;}
			else if(F=='N')
				return;
			else break;
	  }
  }
}


//管理教师信息库功能
void manage_te(void)
{int code,status;
char temp[10],F;
 Link H;
 H=read_te();
 while(1)
 {
 printf("*****************************************************\n");
 printf("                  1) 查看教师信息                \n");
 printf("                  2) 修改教师信息                \n");
 printf("                  3) 添加教师信息                \n");
 printf("                  4) 删除教师信息			\n");
 printf("                  5)   保存修改			\n");
 printf("                  6)     返回			\n");
 printf("*****************************************************\n");
 printf("请选择您的操作: ");
 while((status=scanf("%d",&code))!=1||code<1||code>6)
 	{if(status!=1)
		scanf("%*s");
	printf("请重新选择,输入数字1－6\n");
	printf("请选择您的操作: ");
	}
gets(temp);
switch(code)
	{
	 case 1:refer_te(H);
			break;
	 case 2:modify_teinfo(H);
			break;
     case 3:insert_te(H);
			break;
	 case 4:delete_te(H);
			break;
	 case 5:printf("确定保存您此次的修改?(Y/N)");
			if(getchar()=='Y')
				{save_te(H);break;}
			else 
	          break;
	 case 6:printf("退出请确认(Y-保存并退出,N-不保存退出,其他键取消)");
	 		if((F=getchar())=='Y')
			  {save_te(H);return;}
	 		else if(F=='N')
				return;
			else break;
	}
 }
}


//查询教师信息功能菜单
void refer_te(Link H)
{
int code,status;
char temp[10];
while(1)
{
printf("********************************************************\n");
printf("                   1) 按教师编号查询                \n");
printf("                   2) 按教师姓名查询                \n");
printf("                   3) 查看所有教师信息              \n");
printf("                   4)     返回                      \n");
printf("********************************************************\n");
printf("请选择您的操作: ");
while((status=scanf("%d",&code))!=1||code<1||code>4)
	{if(status!=1)
		scanf("%*s");
	printf("请重新选择,输入数字1－4\n");
	printf("请选择您的操作: ");
 	}
gets(temp);
switch(code)
	{
	 case 1:display_tenum(H);
			break;
	 case 2:display_tename(H);
			break;
	 case 3:display_allte(H);
			break;
	 case 4:printf("您确定要返回?(Y/N)");
			if(getchar()=='Y')
				return;
			else break;
	}
  }
}

//管理员修改教师信息
void modify_teinfo(Link H)
{
 int code,status,number;
 char temp[10],F;
 Teacher *s;
 printf("请输入要修改的教师的编号:");
 scanf("%d",&number);
 s=search_te(H,number);
 if(s==NULL)
 	{printf("您选择的教师不存在\n");
	 return;}
	
while(1)
{display_te(s);
printf("***************请选择要修改的信息**************\n");
printf("                 1) 修改姓名               \n");
printf("                 2) 修改密码               \n");
printf("                 3) 修改班级               \n");
printf("                 4) 保存修改               \n");
printf("                 5)   返回                 \n");
printf("***********************************************\n");
printf("请选择您的操作: ");
while((status=scanf("%d",&code))!=1||code<1||code>5)
	{if(status!=1)
		scanf("%*s");
	printf("请重新选择,输入数字1－5\n");
	printf("请选择您的操作: ");
	}
gets(temp);
switch(code)
	{
	 case 1:printf("请输入新的姓名:");
			scanf("%s",s->te_name);
			break;
	 case 2:printf("请输入新的密码:");
			scanf("%s",s->te_password);
			break;
	 case 3:printf("请输入新的班级:");
			scanf("%d",&(s->te_class));
			break;
	 case 4:printf("确认保存您的修改?(Y/N)");
			if(getchar()=='Y')
			 {save_te(H);break;}
			else
			  break;
	 case 5:printf("退出请确认(Y-保存修改并退出,N-不保存退出,其他键取消)");
			if((F=getchar())=='Y')
				{save_te(H);return;}
			else if(F=='N')
				return;
			else break;
	  }
    }
}

