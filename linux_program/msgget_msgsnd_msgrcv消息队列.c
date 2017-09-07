#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>							//  1 2 3 msgget	msgsnd	msgrcv
#include<stdio.h>
#include<string.h>
//消息队列，一旦消息取了，就没有了，和管道有点类似
struct msg
{
	long type;								//   存放消息的信号
	char data[100];						// 规定 只有两个参数     而且第一个必须long  第二个 字符型
};
int main()
{
	key_t key;
	int msgid;
	
	struct msg msgbuf;
	struct msg msgbuf1;
	
	key=ftok("/home/dong/rm.dong",1);			// 获取文件的 键值	第二个参数（标准位）只要不是0即可
	printf("key=%x\n",key);
	
	msgid=msgget((key_t)1234,IPC_CREAT|0666);		// 创建消息队列  获取队列 ID
	
	msgbuf.type=1;							//  可以为任意值     这只是一个消息的标志		但下面要获取消息就需要	这个标志
	strcpy(msgbuf.data,"hello 11111");		// 创建一个消息
	msgbuf1.type=2;							//	创建第二个消息
	strcpy(msgbuf1.data,"hello 222222");		
	
	msgsnd(msgid,	&msgbuf,	sizeof(msgbuf.data),	0);		// 发送信号 	
	msgsnd(msgid,	&msgbuf1,	sizeof(msgbuf1.data),	0);		// 发送第二个信号
	
	memset(&msgbuf,0,sizeof(msgbuf));		// 删除结构体里面的数据	其实就是	 为了少创建一个空结构体
	memset(&msgbuf1,0,sizeof(msgbuf1));
	
	msgrcv(msgid,	&msgbuf,	sizeof(msgbuf.data),	2,0);	// 第四个参数 就是消息的标志		他就是选择获取那个标志的 ，信号
	msgrcv(msgid,	&msgbuf1,	sizeof(msgbuf1.data),	1,0);
	
	printf("receive first data=%s\n",msgbuf.data);
	printf("receive second data=%s\n",msgbuf1.data);
	
	if (msgctl(msgid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
	}
}
/*
3. msgrcv函数
该函数从一个消息队列中获取消息:
int msgrcv(int msqid, void *msg_ptr, size_t msg_sz, long int msgtype, int msgflg);
参数:
msqid  : 由msgget函数返回的消息队列标识符;
msg_ptr: 一个指向准备接收消息的指针，
         和前面介绍的一样，
         要以一个长整形成员变量开始。
msg_sz : 是msg_ptr指向的消息的长度，
         它不包括长整形消息成员变量的长度。
msgtype: 是一个长整形，
         它可以实现一个简单形式的接收优先级。
         == 0, 将获取队列中的第一个可用消息;
         >  0, 将获取具有相同消息类型的第一个消息;
         <  0, 将获取消息类型 <= msgtype的绝对值的第一个消息。

如果 只想按消息发送的顺序来接收它们，
     就把msgtype设置为0.
如果 只想获取某一特定类型的消息，
     就把msgtype设置为相应的类型值。
如果 只想接收类型 <= n的消息，
     就把msgtype设置为-n.

msgflg: 用于控制当队列中没有相应类型的消息可以接收时将发送的事情。
        如果 msgflg中的IPC_NOWAIT标志被设置，
             函数立即返回-1.
        如果 msgflg中的IPC_NOWAIT标志被消除，
             进程将会挂起以等待一条相应类型的消息到达。

返回值:
成功时， 函数返回放到接收缓存区中的字节数，
         消息被复制到由msg_ptr指向的用户分配的缓存中。
         然后删除消息队列中对应的消息。
失败时， 返回-1.
*/
//Linux内核源码里面的
/* resource get request flags */
#define IPC_CREAT  00001000   /* create if key is nonexistent */
#define IPC_EXCL   00002000   /* fail if key exists */
#define IPC_NOWAIT 00004000   /* return error on wait */

/* these fields are used by the DIPC package so the kernel as standard
   should avoid using them if possible */
   
#define IPC_DIPC 00010000  /* make it distributed */
#define IPC_OWN  00020000  /* this machine is the DIPC owner */

/* 
 * Control commands used with semctl, msgctl and shmctl 
 * see also specific commands in sem.h, msg.h and shm.h
 */
#define IPC_RMID 0     /* remove resource */
#define IPC_SET  1     /* set ipc_perm options */
#define IPC_STAT 2     /* get ipc_perm options */
#define IPC_INFO 3     /* see ipcs */
