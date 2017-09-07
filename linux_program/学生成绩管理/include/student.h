#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//结构变量定义
struct info_personal
{
 int number;
 char name[128];
 char password[32];
 int age;
 int class;
};
struct info_study
{
int math;
int c_language;
int chinese;
int rank;
};
typedef struct stu
{
struct info_personal Person;
struct info_study Study;
struct stu *prior,*next;
}Student,*Linklist;



//函数声明
Linklist creat(void);//创建学生信息库，返回信息库的地址
void input(Student *p);//输入一个学生的信息
int repeat_number(const Student *s,int n);//查询学号是否重复，重复学号返回1，否则返回0
Student *search_number(const Linklist L,int n);//按学号查找学生，返回该学生指针,否则NULL
Student **search_class(const Linklist L,int clas);//根据班级群体查找，返回指针数组的首地址
Student *search_name(const Linklist L,char na[]);//根据姓名查询，返回该学生的指针
void display(const Student *s);//显示一个学生的信息
void display_all(const Linklist L);//显示所有学生信息列表
void delete_stu(Linklist L);//删除链表L中的学生的信息
void rank_score(Student *s);//计算某学生总成绩名次
void sort_number(Linklist L);//按学号对学生顺序排序
void sort_rank(Linklist L);//根据学生名次顺序排序
void sort_math(Linklist L);//根据数学成绩排序
void sort_c_language(Linklist L);//根据c语言成绩排序
void sort_chinese(Linklist L);//根据语文成绩排序
void save(const Linklist L);//保存链表数据到文件
Linklist read(void);//从文件中读取数据并建立链表，返回链表头指针

