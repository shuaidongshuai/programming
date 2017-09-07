#include <iostream>
#include <vector>
using namespace std;

class Slab
{
private:
	union{
		Slab *head;
		Slab *next;
	};
	int slabSize;//slab总容量
	int perslab;//每个 slab 可以切分成多少个 chunk
	int chunkSize;
public:
	vector<Slab *> slab_list;//每个新Slab的起始地址
	int memAll;//总容量
	int memAvail;//可用容量
	int count;//new了几个Slab
private:
	void addMem()
	{
		try
		{
			head = (Slab *)new char[slabSize];
		}
		catch (const bad_alloc &err)
		{
			cout << "new Slab失败" << endl;
			return;
		}
		Slab *temp = head;
		for (int i = 0; i < perslab - 1; ++i)
		{
			temp->next = (Slab *)((char *)temp + chunkSize);
			temp = temp->next;
		}
		temp->next = NULL;
		slab_list.push_back(head);
		++count;
		memAll += slabSize;
		memAvail += slabSize;
	}
public:
	Slab(){}
	~Slab()
	{
		for (vector<Slab*>::iterator it = slab_list.begin(); it != slab_list.end(); ++it)
			delete (char *)*it;
	}
	bool init(int slabSize, int chunkSize)
	{
		this->slabSize = slabSize;
		this->chunkSize = chunkSize;
		this->memAll = 0;
		this->memAvail = 0;
		this->count = 0;
		this->head = NULL;
		perslab = slabSize / chunkSize;
		if (perslab <= 0)
			return false;
		//////////////本来可以在使用的时候再new内存(就和懒汉式和饿汗式思想差不多)这里用饿汗式////////////////
		addMem();
		return true;
	}
	void *getChunk()
	{
		if (!head)
			addMem();
		Slab *cur = head;
		head = head->next;
		memAvail -= chunkSize;
		return (void *)cur;
	}
	void removeChunk(void *ptr)
	{
		Slab *pre = (Slab *)ptr;
		pre->next = head;
		head = pre;
		memAvail += chunkSize;
		ptr = NULL;
	}
	int getChunkSize()
	{
		return chunkSize;
	}
	int getSlabSize()
	{
		return slabSize;
	}
	int getPerslab()
	{
		return perslab;
	}
};

class SlabAlloction
{
private:
	Slab *slabClass;
	int slabClassNum;
	double ratio;//每个slabClass 增长的比例
public:
	SlabAlloction(int chunkSize = 64, int slabSize = 1024 * 1024, int slabClassNum = 10, double ratio = 1.5)//一个Slab默认1M大小
		:slabClassNum(slabClassNum), ratio(ratio)
	{
		if (chunkSize < 4)
			chunkSize = 4;//必须大于4B
		try
		{
			slabClass = new Slab[slabClassNum];
		}
		catch (const bad_alloc &err)
		{
			cout << "new slabClass失败" << endl;
			return;
		}
		for (int i = 0; i < slabClassNum; ++i)
		{
			if (!slabClass[i].init(slabSize, chunkSize))
			{
				cout << "slabClass" << i << "创建失败 （ chunkSize > slabSize ）" << endl;
				return;
			}
			chunkSize *= ratio;
		}
	}
	~SlabAlloction()
	{
		delete[]slabClass;
	}
	int findSuitSlab(int size)
	{
		int i = 0;
		for (; i < slabClassNum; ++i)
			if (slabClass[i].getChunkSize() >= size)
				break;
		return i;
	}
	void *salloc(int size)
	{
		int suitslab = findSuitSlab(size);
		if (suitslab == slabClassNum)
		{
			cout << "Slab内存不够大" << endl;
			return NULL;
		}
		return slabClass[suitslab].getChunk();
	}
	void sfree(void *ptr)
	{
		int size = ((Slab *)ptr)->getChunkSize();
		for (int i = 0; i < slabClassNum; ++i)
		{
			int count = slabClass[i].count;
			for (int j = 0; j < count; ++j)
			{
				if (slabClass[i].slab_list[j] < ptr &&
					slabClass[i].slab_list[j] + slabClass[i].getSlabSize() > ptr)
				{
					slabClass[i].removeChunk(ptr);
					ptr = NULL;
					return;
				}
			}
		}
		cout << "回收0x" << ptr << "内存失败" << endl;
	}
	int getSlabClassNum()
	{
		return slabClassNum;
	}
	void showSlabClassChunk()
	{
		for (int i = 0; i < slabClassNum; ++i)
		{
			cout << "slabClass" << i << endl;
			cout << "总容量：" << slabClass[i].memAll << endl;
			cout << "可用容量：" << slabClass[i].memAvail << endl;
			cout << "new了几个Slab：" << slabClass[i].count << endl;
			cout << "SlabSize:" << slabClass[i].getSlabSize() << endl;
			cout << "ChunkSize:" << slabClass[i].getChunkSize() << endl;
			cout << "Perslab:" << slabClass[i].getPerslab() << endl;
			cout << "--------------------------------------" << endl;
		}
	}
};