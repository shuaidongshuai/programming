#include <time.h>
#include <event.h>

struct event ev;
struct timeval tv;  
void time_cb(int fd, short event, void *argc)  
{
    printf("timer wakeup/n");  
    event_add(&ev, &tv); // reschedule timer  
}
int main()
{  
    struct event_base *base = event_init();//首先初始化libevent库，并保存返回的指针
    tv.tv_sec = 5;
    tv.tv_usec = 0;  
    evtimer_set(&ev, time_cb, NULL);	//初始化事件event，设置回调函数和关注的事件
    event_add(&ev, &tv);  				//添加事件 5s后执行
    event_base_dispatch(base);  		//程序进入无限循环，等待就绪事件并执行事件处理
}
