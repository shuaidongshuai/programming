


void menu(void);//登录总菜单
int load_stu(Linklist L);//学生登录功能
int load_te(Link H);//教师登录功能
int load_manager(void);//管理员登录功能



void menu_stu(Linklist L,int number);//学生功能菜单
void modify_stu(Linklist L,Student *s);//学生修改个人信息功能菜单
void changepass(Student *s);//学生修改密码功能


void menu_tea(Link H,Linklist L,int number);//教师功能菜单
void modify_te(Link H,Teacher *s);//教师修改个人信息功能菜单
void changepass_te(Teacher *s);//教师修改密码功能
void refer_stu(Linklist L);//查看学生信息菜单
void refer_study(Linklist L);//查看学生成绩功能
void modify_study(Linklist L);//教师修改学生成绩功能
void menu_admin(void);//管理员功能菜单
void manage_stu(void);//管理学生数据库功能
void modify_stuinfo(Linklist L);//管理员修改学生个人信息
void manage_te(void);//管理教师信息库功能
void refer_te(Link H);//查询教师信息功能菜单
void modify_teinfo(Link H);//管理员修改教师信息



