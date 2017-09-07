#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
printf("UID=%d\n",getuid());
printf("EUID=%d\n",geteuid());
printf("group ID =%d\n",getgid());
printf("effective group ID =%d\n",getegid());

return 0;
}
