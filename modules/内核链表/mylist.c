#include<linux/module.h>
#include<linux/init.h>
#include<linux/list.h>
struct score
{
	int num;
	int english;
	int math;
	struct list_head list;			//这个指针  在这个结构体中叫做指针域
};
struct list_head score_head,*pos;
struct score str1,str2,str3,*tmp;
int mylist_init()
{
	INIT_LIST_HEAD(&score_head);	//对内核给你的链表 初始化
	
	//自己定义的结构体  初始化
	str1.num = 1;
	str1.english = 91;
	str1.math = 99;
	list_add_tail(&(str1.list),&score_head);
	
	str2.num = 2;
	str2.english = 91;
	str2.math = 99;
	list_add_tail(&(str2.list),&score_head);	
	
	str3.num = 3;
	str3.english = 91;
	str3.math = 99;
	list_add_tail(&(str3.list),&score_head);	
	
	//#define __list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)    就是一个链表的遍历   只不过内核中给了一个宏给我们用
	//把自己定义的结构体   传入内核给你的链表中去，，，构成自己想要的链表
	list_for_each(pos,&score_head)	//pos相当于一个轮循的指针 在 str1 str2 str3 之间移动
	{
		tmp=list_entry(pos,struct score,list);	//list_entry就相当于访问  在pos指针指到的结构体    最后那个参数就是自己结构体  指针域的名字list
		printk("%d\t%d\t%d\n",tmp->num,tmp->english,tmp->math);
	}
	
	printk("删除\n");
	printk("\n");
	list_del(&(str1.list));

	list_for_each(pos,&score_head)	//pos相当于一个轮循的指针 在 str1 str2 str3 之间移动
	{
		tmp=list_entry(pos,struct score,list);	//list_entry就相当于访问  在pos指针指到的结构体    最后那个参数就是自己结构体  指针域的名字list
		printk("%d\t%d\t%d\n",tmp->num,tmp->english,tmp->math);
	}
	return 0;
}
void mylist_exit()
{
	
}

module_init(mylist_init);
module_exit(mylist_exit);