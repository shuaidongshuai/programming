#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "locker.h"

template< typename T >
class threadpool
{
public:
    threadpool( int thread_number = 8, int max_requests = 10000 );
    ~threadpool();
    bool append( T* request );

private:
    static void* worker( void* arg );
    void run();

private:
	/*最大线程数*/
    int m_thread_number;
	/*最大请求数*/
    int m_max_requests;
	/*所有工作任务链表*/
    std::list< T* > m_workqueue;
	/*互斥锁*/
    locker m_queuelocker;
	/*信号量*/
    sem m_queuestat;
    pthread_t* m_threads;//typedef unsigned long int pthread_t;
    bool m_stop;
};

template< typename T >
threadpool< T >::threadpool( int thread_number, int max_requests ) : 
        m_thread_number( thread_number ), m_max_requests( max_requests ), m_stop( false ), m_threads( NULL )
{
    if( ( thread_number <= 0 ) || ( max_requests <= 0 ) )
    {
        throw std::exception();
    }

    m_threads = new pthread_t[ m_thread_number ];//相当于申请 m_thread_number 个线程id
    if( ! m_threads )
    {
        throw std::exception();
    }
	/*创建线程池*/
    for ( int i = 0; i < thread_number; ++i )
    {
        printf( "create the %dth thread\n", i );
        if( pthread_create( m_threads + i, NULL, worker, this ) != 0 )
        {
            delete [] m_threads;
            throw std::exception();
        }
        if( pthread_detach( m_threads[i] ) )//该线程运行结束后会自动释放所有资源
        {
            delete [] m_threads;
            throw std::exception();
        }
    }
}

template< typename T >
threadpool< T >::~threadpool()
{
    delete [] m_threads;
    m_stop = true;
}

/*对信号量进行加操作 和 往任务队列中加任务*/
template< typename T >
bool threadpool< T >::append( T* request )
{
	/*把任务加入队列需要加锁*/
    m_queuelocker.lock();
    if ( m_workqueue.size() > m_max_requests )//判断当前工作任务是否达到最大
    {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back( request );
    m_queuelocker.unlock();
    m_queuestat.post();//信号量+1
    return true;
}

/*所有子线程都在这开始运行*/
template< typename T >
void* threadpool< T >::worker( void* arg )
{
    threadpool* pool = ( threadpool* )arg;
    pool->run();
    return pool;
}

template< typename T >
void threadpool< T >::run()
{
    while ( ! m_stop )
    {
		/*只要线程跑到这，信号量就-1 , 如果信号量为0就阻塞在这，说明没有任务到来*/
        m_queuestat.wait();
		/*获取任务需要加锁，不能多个线程获取同一个任务*/
        m_queuelocker.lock();
        if ( m_workqueue.empty() )
        {
            m_queuelocker.unlock();
            continue;
        }
        T* request = m_workqueue.front();//取任务队列的第一个
        m_workqueue.pop_front();
        m_queuelocker.unlock();
        if ( ! request )//请求不为空
        {
            continue;
        }
        request->process();//调用user的process函数，也就是调用http_conn.cpp里面的process
    }
}

#endif
/*
创建一个线程默认的状态是joinable, 如果一个线程结束运行但没有被join,则它的状态类似于进程中的Zombie Process,
即还有一部分资源没有被回收（退出状态码），所以创建线程者应该pthread_join来等待线程运行结束，并可得到线程的退出代码，回收其资源（类似于wait,waitpid)
但是调用pthread_join(pthread_id)后，如果该线程没有运行结束，调用者会被阻塞，在有些情况下我们并不希望如此，
比如在Web服务器中当主线程为每个新来的链接创建一个子线程进行处理的时候，主线程并不希望因为调用pthread_join而阻塞（因为还要继续处理之后到来的链接），
这时可以在子线程中加入代码
pthread_detach(pthread_self())
或者父线程调用
pthread_detach(thread_id)（非阻塞，可立即返回）
这将该子线程的状态设置为detached,则该线程运行结束后会自动释放所有资源。
*/
