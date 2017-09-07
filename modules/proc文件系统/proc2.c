#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include<asm/uaccess.h>

static struct proc_dir_entry *mydir,*procfile;

static char msg[100];
//一些参数现在用不着，重点是使用这个函数，这个函数名字可以随便取，但是参数是固定的
static int proc_read(char *page,char **start,off_t off,int count,int *peof,void *data)
{
	int len = strlen(msg);
	if(off>=len)
		return 0;
	if(count>len - off);
	count = len - off;
	
	//void *memcpy(void *dest, const void *src, size_t n);
	//从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中
	memcpy(page+off,msg+off,count);//将msg 中的数据 拷贝到 page 中，也就是 myprofile这个刚创建的文件中去
	return off+count;
}
static int proc_write(struct file *file,const char *buffer,unsigned long count,void *data)
{
	//从键盘输入的东西将存在buffer 指向的内存空间中
	
	if(count>=sizeof(msg))
		count = sizeof(msg) -1;
	
	//unsigned long copy_from_user(void * to, const void __user * from, unsigned long n)用于将用户空间的数据传送到内核空间。
	copy_from_user(msg,buffer,count);//将 buffer 中的数据 拷贝到 msg 中去
	
	msg[count] = '\0';
	return count;
}

static int __init myproc_init(void)
{
	mydir = proc_mkdir("mydir",NULL);//创建文件目录，无父目录
	
	procfile = create_proc_entry("myproc",0666,mydir);//创建peoc文件，父目录为mydir
	
	//在用户或应用程序访问该proc文件时，就会调用这个函数，实现这个函数时只需将想要让用户看到的内容放入page即可。
	procfile->read_proc = proc_read;
	procfile->write_proc = proc_write;
	
	return 0;
}
static void __exit myproc_exit(void)
{
	remove_proc_entry("myproc",mydir);
	remove_proc_entry("mydir",NULL);
}

module_init(myproc_init );
module_exit(myproc_exit);
