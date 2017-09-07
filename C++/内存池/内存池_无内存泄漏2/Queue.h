#include "Mempool.h"
template<typename T>
class QueueItem
{
public:
	QueueItem(T d) :data(d){}
public:
	T data;
	QueueItem *next;
};
template<typename T>
class Queue
{
public:
	Queue()
	{
		head = tail = NULL;
		memPool = new MemPool(5, sizeof(QueueItem<T>));
	}
	~Queue()
	{
		cout << "Queue delete" << endl;
		delete memPool;
	}
	T front()
	{
		if (head)
			return head->data;
		return NULL;
	}
	T back()
	{
		if (tail)
			return tail->data;
		return NULL;
	}
	void push(const T &d)
	{
		QueueItem<T> *cur = (QueueItem<T> *)memPool->getMem();
		cur->data = d;
		if (!head)
			head = tail = cur;
		else
		{
			tail->next = cur;
			tail = cur;
		}
	}
	void pop()
	{
		if (!head)
			return;
		if (head == tail)
		{
			memPool->delMem(head);
			head = tail = NULL;
		}
		else
		{
			QueueItem<T> *cur = head;
			head = head->next;
			memPool->delMem(cur);
		}
	}
	bool empty()
	{
		if (head == NULL && tail == NULL)
			return true;
		return false;
	}
private:
	QueueItem<T> *head;
	QueueItem<T> *tail;
	MemPool *memPool;
};