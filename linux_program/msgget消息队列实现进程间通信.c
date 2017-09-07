#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
struct msgbuf
{
	long msgtype;
	char msgtext[100];
}snd,rcv;
/*系统建立IPC通讯 （消息队列、信号量和共享内存） 时必须指定一个ID值。通常情况下，该id值通过ftok函数得到。*/
int main()
{
	key_t key;
	int msqid;
	char message1[]="hello dong";
	char message2[]="goodbye!";
	key=ftok("/home/dong/dd",1);						//  指定 key
	if(key==-1)
	{
		perror("create key error");
		return 1;
	}
	if((msqid=msgget(key,IPC_CREAT|0666))==-1)			// 创建消息队列
	{
		printf("msgget error");
		return 1;
	}
	snd.msgtype=1;
	strcpy(snd.msgtext,message1);
	if(msgsnd(msqid,&snd,sizeof(message1)+1,0)==-1)		// 发送消息
	{
		printf("msgsnd error\n");
		return 1;
	}
	snd.msgtype=2;
	strcpy(snd.msgtext,message2);
	if(msgsnd(msqid,&snd,sizeof(message2)+1,0)==-1)		// 发送消息
	{
		printf("msgsnd error\n");
		return 1;
	}
	
	if(msgrcv(msqid,&rcv,20,1,0)==-1)					//  接收消息
	{
		printf("msgrcv error");
		return 1;
	}
	printf("the received message:%s\n",rcv.msgtext);
	system("ipcs -q");									//在系统中显示新创建的消息队列的信息
	msgctl(msqid,IPC_RMID,0);							//  删除新创建的消息队列
	return 0;
}