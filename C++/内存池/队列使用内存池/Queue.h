#include "Mempool.h"
template<typename T>
class Queue
{
public:
	Queue()
	{
		prear = pfirst = NULL;
	}
	~Queue()
	{
		MemPool<T> *pcur = pfirst;
		while (pcur != prear)
		{
			pfirst = pfirst->pNext;
			delete pcur;
			pcur = pfirst;
		}
	}
	T front()
	{
		if (!pfirst)
			return NULL;
		return pfirst->data;
	}
	T back()
	{
		if (!prear)
			return NULL;
		return prear->data;
	}
	void push(const T &d)
	{
		/*prear = new MemPool<T>(d);
		if (!pfirst)
			pfirst = prear;*/
		MemPool<T> *p = new MemPool<T>(d);
		if (!prear)
			prear = pfirst = p;
		else
		{
			prear->pNext = p;
			prear = p;
		}
	}
	void pop()
	{
		if (pfirst == prear)
		{
			delete pfirst;
			pfirst = prear = NULL;
		}
		else
		{
			MemPool<T> *pFree = pfirst;
			pfirst = pfirst->pNext;
			delete pFree;
		}
	}
	bool empty()
	{
		if (prear == NULL && pfirst == NULL)
			return true;
		return false;
	}
private:
	MemPool<T> *prear;
	MemPool<T> *pfirst;
};