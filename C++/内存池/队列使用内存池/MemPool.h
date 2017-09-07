#include <iostream>
template<typename T>
class MemPool
{
public:
	MemPool(){ cout << "构造" << endl; }
	MemPool(T data) :data(data){ cout << "构造 data" << endl; }
	~MemPool(){ cout << "析构" << endl; }
	//这两个函数编译器就默认处理成static函数
	void *operator new(size_t size)
	{
		MemPool *pCur;
		if (!pHead)//如果内存不够了，向系统申请内存
		{
			int allocsize = size * MEM_POOL_SIZE;
			cout << "第" << ++count << "向系统申请了" << allocsize << "字节内存" << endl;
			pHead = (MemPool*)new char[allocsize];
			for (pCur = pHead; pCur < pHead + MEM_POOL_SIZE - 1;++pCur)
				pCur->pNext = pCur + 1;
			pCur->pNext = NULL;
		}
		pCur = pHead;
		pHead = pHead->pNext;
		return pCur;//这里只是把其中一片内存给用户了，用户并不能通过 ->pNext 得到下一片内存★★★★★
	}
	/*这里会发生内存溢出，因为根本就没有释放，等我看完memcached再说*/
	void operator delete(void *ptr)
	{
		cout << "MemPool delete" << endl;
		if (!ptr) return;
		MemPool *cur = (MemPool*)ptr;
		cur->pNext = pHead;
		pHead = cur;
	}
public:
	MemPool *pNext;
	static const unsigned int MEM_POOL_SIZE = 10;
	static MemPool *pHead;
	static int count;
	T data;
};
template<typename T>
MemPool<T> *MemPool<T>::pHead = NULL;
template<typename T>
int MemPool<T>::count = 0;