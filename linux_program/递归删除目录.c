#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
 
void dfs_remove_dir()
{
    DIR *cur_dir = opendir(".");
    struct dirent *ent = NULL;
    struct stat st;
 
    if (!cur_dir)
    {
        perror("opendir:");
        return;
    }
    while ((ent = readdir(cur_dir)) != NULL)//读取目录
    {
        stat(ent->d_name, &st);
     
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            continue;
        if (S_ISDIR(st.st_mode))
        {
            chdir(ent->d_name);
            dfs_remove_dir();
            chdir("..");
        }
        remove(ent->d_name);
    }
    closedir(cur_dir);
}
void remove_dir(const char *path_raw)
{
    char old_path[100];
 
    if (!path_raw)
        return;
 
    getcwd(old_path, 100);
     
    if (chdir(path_raw) == -1)//更改当前工作目录
    {
        fprintf(stderr, "not a dir or access error\n");
        return;
    }
    printf("path_raw : %s\n", path_raw);
    dfs_remove_dir();
    chdir(old_path);
    
     //如果你想删除该目录本身的话,取消注释
     remove(old_path); 
}
int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        remove_dir(argv[1]);
    }
 
    return 0;
}
/*
getcwd
getcwd
函数原型：char *getcwd( char *buffer, int maxlen );
功 能：获取当前工作目录

函数原型
DIR* opendir (const char * path );
功能
打开一个目录，在失败的时候返回一个空的指针。

struct dirent *readdir(DIR *dirp);
DESCRIPTION
       The readdir() function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed
       to by dirp.  It returns NULL on reaching the end of the directory stream or if an error occurred.//representing 代表
	   返回一个指向dirent结构体的指针，
	   如果到达末尾，或者error返回NULL
struct dirent {
	ino_t          d_ino;       inode number 				
	off_t          d_off;       not an offset; see NOTES	在目录文件中的偏移
	unsigned short d_reclen;    length of this record 		文件名长 
	unsigned char  d_type;      type of file; not supported	文件类型 
								by all filesystem types 	
	char           d_name[256]; filename 					文件名，最长255字符
};


int stat(const char *file_name, struct stat *buf);
函数说明:    通过文件名filename获取文件信息，并保存在buf所指的结构体stat中
返回值:      执行成功则返回0，失败返回-1，错误代码存于errno
struct stat {
    dev_t         st_dev;       //文件的设备编号
    ino_t         st_ino;       //节点
    mode_t        st_mode;      //文件的类型和存取的权限
    nlink_t       st_nlink;     //连到该文件的硬连接数目，刚建立的文件值为1
    uid_t         st_uid;       //用户ID
    gid_t         st_gid;       //组ID
    dev_t         st_rdev;      //(设备类型)若此文件为设备文件，则为其设备编号
    off_t         st_size;      //文件字节数(文件大小)
    unsigned long st_blksize;   //块大小(文件系统的I/O 缓冲区大小)
    unsigned long st_blocks;    //块数
    time_t        st_atime;     //最后一次访问时间
    time_t        st_mtime;     //最后一次修改时间
    time_t        st_ctime;     //最后一次改变时间(指属性)
};

一般在之前都会先调用函数stat( FileName, &fp)，意味着将FileName这个文件的信息保存到了地址fp中。此时fp.st_mode就是文件FileName的模式，
所以S_ISDIR(fp.st_mode)的函数功能是判断fp所指向文件（也就是FileName）是否为目录（dir）类型。
*/