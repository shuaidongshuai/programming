#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <vector>
#include <exception>
#include <pthread.h>
#include "locker.h"
// #include <iostream>
// using namespace std;

template<typename T>
class ThreadPool{
public:
	ThreadPool(unsigned int minPthreadNum = 10, unsigned int maxPthreadNum = 1024):
		minPthreadNum(minPthreadNum),maxPthreadNum(maxPthreadNum),chiPthreads(minPthreadNum)
	{
		if(minPthreadNum <= 0 || maxPthreadNum <= 0)
			throw std::exception();
		//创建线程池
		for(int i = 0; i < minPthreadNum; ++i){
			if(pthread_create(&chiPthreads[i], 0, Work, this))
				throw std::exception();
			if(pthread_detach(chiPthreads[i]))
				throw std::exception();
			++curPthreadNum;
		}
		//cout<<"创建线程池 num = "<<curPthreadNum<<endl;
	}
	~ThreadPool(){
		stop = true;
	}
	static void *Work(void* arg){
		ThreadPool *pool = (ThreadPool *)arg;
		pool->run();
	}
	void run(){
		while(!stop){
			/*只要线程跑到这，信号量就-1 , 如果信号量为0就阻塞在这，说明没有任务到来*/
			semLock.wait();
			/*获取任务需要加锁，不能多个线程获取同一个任务*/
			queueLock.lock();
			if(workQueue.empty()){
				//打印错误日志
				continue;
			}
			T *request = workQueue.front();
			workQueue.pop_front();
			queueLock.unlock();

			/* run要在用户自己类中实现 */
			request->run();

			//任务执行完后
			numLock.lock();
			--curRequestNum;//任务 - 1
			//自动调整线程池大小
			if(curPthreadNum > minPthreadNum && curPthreadNum > curRequestNum){
				--curPthreadNum;
				numLock.unlock();
				//cout<<"减少线程"<<endl;
				return;
			}
			numLock.unlock();
		}
	}
	bool append(T *request){
		queueLock.lock();
		workQueue.push_back(request);
		semLock.post();
		queueLock.unlock();

		bool isCreate = false;
		int curNum;
		numLock.lock();
		++curRequestNum;//任务 + 1
		/*当前请求个数大于当前线程个数 就创建新线程*/
		if(curRequestNum > curPthreadNum && curRequestNum < maxPthreadNum){
			curNum = ++curPthreadNum;//线程 + 1
			isCreate = true;
		}
		numLock.unlock();

		if(isCreate){
			chiPthreads.push_back(0);
			if(pthread_create(&chiPthreads[curNum], 0, Work, this))//创建新线程
				throw std::exception();
			if(pthread_detach(chiPthreads[curNum]))
				throw std::exception();
			//cout<<"创建新线程"<<endl;
		}
		return true;
	}
private:
	unsigned int maxPthreadNum;//最大的线程数
	unsigned int minPthreadNum;//最小的线程个数
	unsigned int curPthreadNum = 0;//当前线程个数
	unsigned int curRequestNum = 0;//当前任务个数
    std::list<T*> workQueue;//所有工作任务链表
    std::vector<pthread_t> chiPthreads;//子线程num
    Locker queueLock;/*用于队列的 互斥锁*/
    Locker numLock;/*用于个数的 互斥锁*/
    Sem semLock;/*信号量*/
    bool stop = false;//关闭pthreadPool
};
#endif