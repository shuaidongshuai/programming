#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/proc_fs.h>

struct proc_dir_entry *Our_proc_file;

int procfile_read(char *buffer,char **stat,off_t off,int count,int *peof,void *data)
{
	int ret = sprintf(buffer,"Hello,dong\n");
	return ret;
}

int proc_init()
{
	Our_proc_file = create_proc_entry("myproc",0644,NULL);//创建proc文件
	if(Our_proc_file == NULL)
	{
		printk("error");
		return 0;
	}
	Our_proc_file->read_proc = procfile_read;//向文件中写入数据
	Our_proc_file->gid = 0;//设置文件属性
	Our_proc_file->uid = 0;
	Our_proc_file->size = 66;
	printk("procfile creat success\n");
	return 0;
}

void proc_exit()
{
	remove_proc_entry("myproc",NULL);//删除proc文件
	printk("procfile remove success\n");
}

module_init(proc_init);
module_exit(proc_exit);