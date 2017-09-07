//结构声明
typedef struct tea
{
int te_number;
char te_name[128];
char te_password[32];
int te_class;
struct tea *prior,*next;
}Teacher,*Link;



//教师函数声明
Link creat_te(void);//创建教师信息库
void input_te(Teacher *s);//录入一个教师的信息
int repeat_num(const Teacher *s,int n);//查询教师编号是否重复，重复返回1，否则返回0
void display_te(const Teacher *s);//显示一个教师的信息
void save_te(const Link H);//保存链表数据到文件
Link read_te(void);//从文件中读取数据并建立链表，返回链表头指针
void display_number(const Linklist L);//根据学号查看一个学生信息
void display_name(const Linklist L);//根据姓名查看学生信息；
void display_class(const Linklist L);//根据班级显示该班级所有的学生信息
void rank_new(Linklist L);//根据新的成绩计算所有学生的名词
Teacher *search_te(const Link H,int n);//根据教师编号查询，返回教师的指针，否则返回NULL


