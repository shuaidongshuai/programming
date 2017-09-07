#include <iostream>
#include <list>
using namespace std;

class MemPool
{
private:
	void addMem()
	{
		if (chunkSize < 4)
			chunkSize = 4;
		int allocsize = chunkSize * size;//开辟的总大小
		pHead = (Chunk *)new char[allocsize];
		Chunk *pCur = pHead;
		for (int i = 0; i < size - 1;++i)
		{
			pCur->pNext = (Chunk *)((char *)pCur + chunkSize);
			pCur = pCur->pNext;
		}
		pCur->pNext = NULL;
		//memList.push_back(pHead);
		cout << "第" << ++count << "向系统申请了" << allocsize << "字节内存" << endl;
	}
public:
	MemPool(unsigned int size = 5, unsigned int chunkSize = 1024)
		:size(size), count(0), chunkSize(chunkSize)
	{ cout << "构造" << endl; }
	~MemPool()
	{
		cout << " 析构" << endl;
		/*for (list<Chunk *>::iterator it = memList.begin(); it != memList.end(); ++it)
			delete *it;*/
	}
	void *getMem()
	{
		Chunk *pCur;
		if (!pHead)//如果内存不够了，向系统申请内存
			addMem();
		pCur = pHead;
		pHead = pHead->pNext;
		return (void *)pCur;
	}
	void delMem(void *ptr)
	{
		if (!ptr) return;
		Chunk *cur = (Chunk *)ptr;
		cur->pNext = pHead;
		pHead = cur;
	}
	class Chunk
	{
	public:
		Chunk *pNext;
	};
public:
	//list<Chunk *> memList;//不需要这个，因为根本不存在内存泄漏，只是new出来到程序结束没有delete而已，这个不叫内存泄漏，内存泄漏是会导致系统所有内存被占用完
	unsigned int size;//chunk个数
	unsigned int chunkSize;//chunk大小
	Chunk *pHead;
	Chunk *pNext;
	int count;
};