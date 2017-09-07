#ifndef LOCKER_H
#define LOCKER_H

#include <exception>
#include <pthread.h>
#include <semaphore.h>

/*POSIX信号量*/
class sem
{
public:
    sem()
    {
		/*初始化一个信号量   注意：不能初始化一个初始化的信号量*/
        if( sem_init( &m_sem, 0, 0 ) != 0 )//2.信号量类型（如果是0，表示当前进程局部信号量） 3.信号量的初始值
        {
            throw std::exception();
        }
    }
    ~sem()
    {
        sem_destroy( &m_sem );
    }
    bool wait()
    {
        return sem_wait( &m_sem ) == 0;//以原子操作的方式将信号量减1，如果为0就阻塞
    }
    bool post()
    {
        return sem_post( &m_sem ) == 0;//以原子操作的方式将信号量加1
    }
	/*上面函数成功返回0，失败返回-1，并设置errno*/
private:
    sem_t m_sem;
};
/*互斥锁*/
class locker
{
public:
    locker()
    {
        if( pthread_mutex_init( &m_mutex, NULL ) != 0 )//2.属性（NULL表示默认）
        {
            throw std::exception();
        }
    }
    ~locker()
    {
        pthread_mutex_destroy( &m_mutex );
    }
    bool lock()
    {
        return pthread_mutex_lock( &m_mutex ) == 0;//原子操作，进行加锁,如果已经加锁就阻塞
    }
    bool unlock()
    {
        return pthread_mutex_unlock( &m_mutex ) == 0;//原子操作，解锁
    }
private:
    pthread_mutex_t m_mutex;
};
/*条件变量*/
class cond
{
public:
    cond()
    {
		/*一般条件变量和互斥锁一起用*/
        if( pthread_mutex_init( &m_mutex, NULL ) != 0 )
        {
            throw std::exception();
        }
        if ( pthread_cond_init( &m_cond, NULL ) != 0 )
        {
            pthread_mutex_destroy( &m_mutex );
            throw std::exception();
        }
    }
    ~cond()
    {
        pthread_mutex_destroy( &m_mutex );
        pthread_cond_destroy( &m_cond );
    }
    bool wait()
    {
        int ret = 0;
        pthread_mutex_lock( &m_mutex );//在使用条件变量的时候，一定要确保加锁了
        ret = pthread_cond_wait( &m_cond, &m_mutex );
        pthread_mutex_unlock( &m_mutex );
        return ret == 0;
    }
    bool signal()
    {
        return pthread_cond_signal( &m_cond ) == 0;
    }

private:
    pthread_mutex_t m_mutex;
    pthread_cond_t m_cond;
};

#endif
