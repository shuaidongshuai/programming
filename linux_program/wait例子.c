 #include <stdio.h>
 #include <sys/types.h>
 #include <unistd.h>
#include <wait.h>
 #include <stdlib.h>
 void waitprocess();
 int main(int argc, char * argv[])
{
  waitprocess(); 
 }

void waitprocess()
{

   int count = 0;
   pid_t pid = fork();
  int status ;
  if(pid<0)
  {
    printf("fork error" );
   }
   else if(pid>0)
  {
    printf("this is parent ,pid = %d\n",getpid() );
    wait(&status);//父进程执行到此，马上阻塞自己，直到有子进程结束。当发现有子进程结束时，就会回收它的资源。
       }
	else
  {
    printf("this is child , pid = %d , ppid = %d\n",getpid(),getppid() );
    int i;
    
     for (i = 0; i < 10; i++)
	 {
	count++;
    printf("count = %d\n", count)  ;
    }
     exit(5);
  }
  printf("child exit status is %d\n", WEXITSTATUS(status));//status是按位存储的状态信息，需要调用相应的宏来还原一下
  printf("end of program from pid = %d\n",getpid() );
 }