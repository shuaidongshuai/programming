#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

void removeAll()
{
	DIR *cur_dir = opendir(".");//目录需要打开才能操作里面的东西
	struct dirent *ent = NULL;		//为了获得当前目录下每一个文件的文件名
	struct stat st;				//为了判断一个文件是否为目录

	if (!cur_dir)
    {
	   perror("opendir:");
	   return;
	}
	
	
	while((ent = readdir(cur_dir)) != NULL)//readddir每次调用都会下一个文件的dirent结构体
	{
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)//如果当前目录名是. .. 就不做任何操作
		    continue;

		stat(ent->d_name,&st);//利用文件名获取stat结构体，目的就是为了判断当前文件是否是一个目录

		if(S_ISDIR(st.st_mode))//判断是不是目录，如果是目录需要递归
		{
			chdir(ent->d_name);//进入
			removeAll();
			chdir("..");//回来
		}
		remove(ent->d_name);
	}
	closedir(cur_dir);//关闭目录
}

void removeDir(const char*path)
{
	if(!path)
	  return;

	char cur_path[100];

	getcwd(cur_path,sizeof(cur_path));//获取当前路径

	if(chdir(path )== -1)//进入到我们需要删除的目录文件
	{
		perror("chdir");
		return;
	}
	
	/*递归删除当前文件下面的所有文件*/
	removeAll();

	chdir(cur_path);//回到当前目录

	remove(path);//删除我们指定的文件目录
}

int main(int argc,char** argv)
{
	if(argc != 2)
	  return 0;
	removeDir(argv[1]);
	return 0;
}
