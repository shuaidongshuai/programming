#include <iostream>
template<typename T>
class MemPool
{
public:
	MemPool(T data) :data(data)
	{
		cout << "MemPool" << endl;
	}
	~MemPool()
	{
		cout << "~MemPool" << endl;
	}
	//这两个函数编译器就默认处理成static函数
	void *operator new(size_t size)
	{
		cout << "MemPool new" << endl;
		MemPool *pCur;
		if (!pHead)
		{
			int allocsize = size * MEM_POOL_SIZE;
			pHead = (MemPool*)new char[allocsize];
			for (pCur = pHead; pCur < pHead + MEM_POOL_SIZE - 1; ++pCur)
				pCur->pNext = pCur + 1;
			pCur->pNext = NULL;
		}
		pCur = pHead;
		pHead = pHead->pNext;
		return pCur;
	}
	void operator delete(void *ptr)
	{
		cout << "MemPool delete" << endl;
		if (!ptr) return;
		MemPool *cur = (MemPool*)ptr;
		cur->pNext = pHead;
		pHead = cur;
	}
private:
	static const unsigned int MEM_POOL_SIZE = 10;
	static MemPool *pHead;
	MemPool *pNext;
	T data;
};
template<typename T>
MemPool<T> *MemPool<T>::pHead = NULL;