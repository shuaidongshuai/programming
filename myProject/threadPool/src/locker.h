#ifndef LOCKER_H
#define LOCKER_H
#include <exception>
#include <pthread.h>
#include <semaphore.h>

//信号量
class Sem{
public:
	Sem(){
		if(sem_init(&sem, 0, 0))
			throw std::exception();
	}
	~Sem(){
		sem_destroy(&sem);
	}
	bool wait(){
		return sem_wait(&sem) == 0;// - 1
	}
	bool post(){
		return sem_post(&sem) == 0;// + 1
	}
private:
	sem_t sem;
};
//互斥锁
class Locker{
public:
	Locker(){
		if(pthread_mutex_init(&mutex, 0))
			throw std::exception();
	}
	~Locker(){
		pthread_mutex_destroy(&mutex);
	}
	bool lock(){
        return pthread_mutex_lock(&mutex) == 0;
    }
    bool unlock(){
        return pthread_mutex_unlock(&mutex) == 0;
    }
private:
	pthread_mutex_t mutex;
};

#endif