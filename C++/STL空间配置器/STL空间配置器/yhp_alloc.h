#ifndef YHP_ALLOC_H
#define YHP_ALLOC_H

namespace yhp
{
#if 0
#include<new>
#define __THROW_BAD_ALLOC throw std::bad_alloc()
#elif !defined(__THROW_BAD_ALLOC)
#include<iostream>
#define __THROW_BAD_ALLOC std::cerr<<"out of memory"<<std::endl; exit(1)
#endif

/*一级空间配置器*/
template<int inst>
class __malloc_alloc_template
{
private:
	/*下面两个函数都是内存不足时调用的*/
	static void *oom_malloc(size_t n)
	{
		void(*my_malloc_handler)() = NULL;
		void *result = NULL;
		for (;;)
		{
			my_malloc_handler = __malloc_alloc_oom_handler;
			if (NULL == my_malloc_handler)
			{
				__THROW_BAD_ALLOC;
			}
			(*my_malloc_handler)();
			result = malloc(n);
			if (NULL != result)
				return result;
		}
	}
	static void *oom_realloc(void *p, size_t n)
	{
		void(*my_malloc_handler)() = NULL;
		void *result = NULL;
		for (;;)
		{
			my_malloc_handler = __malloc_alloc_oom_handler;
			if (NULL == my_malloc_handler)
			{
				__THROW_BAD_ALLOC;
			}
			(*my_malloc_handler)();
			result = realloc(p, n);
			if (NULL != result)
				return result;
		}
	}
	/*这个函数指针可以指向一个可以释放内存的函数，被上面两个函数判断如果有释放内存的函数就调用这个函数*/
	static void(*__malloc_alloc_oom_handler)();
public:
	static void *allocate(size_t n)
	{
		void * result = malloc(n);
		if (result == NULL)
		{
			result = oom_malloc(n);
		}
		return result;
	}
	static void deallocate(void *p, size_t/* n*/)
	{
		free(p);
	}
	static void *reallocate(void *p, size_t /*old_sz*/, size_t new_sz)
	{
		void *result = realloc(p, new_sz);
		if (NULL == result)
		{
			result = oom_realloc(p, new_sz);
		}
		return result;
	}

	static void(*set_malloc_handler(void(*f)()))()
	{
		void(*old)() = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler = f;
		return old;
	}
};

typedef __malloc_alloc_template<0> malloc_alloc;

#if 0
//如果觉得没必要释放内存就把__malloc_alloc_oom_handler = NULL
template<int inst>
void(*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = NULL;
#else
//如果觉得内存池很有可能申请不到内存
char *preMem = new char[1024 * 1024 * 10];//可以先new出10M内存出来
void delPreMem()
{
	delete preMem;//释放最开始申请的内存
}
template<int inst>
void(*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = delPreMem;
#endif

/*二级空间配置器*/
enum { __ALIGN = 8 };							//每个chunk之间的间隔 0 8 16 24
enum { __MAX_BYTES = 128 };						//最大的chunk
enum { __NFREELISTS = __MAX_BYTES / __ALIGN };	//list里面有几种chunk
template<bool threads, int inst>
class __default_malloc_template
{
private:
	union obj
	{
		union obj * free_list_link;				//下一个相同chunk大小的地址
		char client_data[1];
	};

	static obj * volatile free_list[__NFREELISTS];//自由链表，一共16个元素
	/*上调bytes至8的倍数*/
	static size_t ROUND_UP(size_t bytes)
	{
		return (bytes + __ALIGN - 1) & ~(__ALIGN - 1);//和  (bytes + 7) / 8 * 8;原理一样,先向右移动3位再向左移动3位 和 与0x11111000的效果一样
	}
	/*找到bytes在free_list中的位置*/
	static size_t FREELIST_INDEX(size_t bytes)
	{
		//return (bytes + __ALIGN - 1) / __ALIGN - 1;//STL上面是这样写的不过下面这样做更好
		return ((bytes + __ALIGN - 1) >> 3) - 1;
	}

	static char * start_free;//内存池起始地址
	static char * end_free;//内存池末尾地址
	static size_t heap_size;//已经开辟的堆大小
	/*
	专门给free list提供内存的"内存池"
	分配一大块空间(size * nobjs) size是用户现在需要的大小(但是我们不能用户需要多少给多少啊，给多一点放在内存池中管理)
	但是如果当前内存池中的空闲内存没有那么大，nobjs能取多少就取多少(这样就能不需要malloc申请内存了啊)
	*/
	static char *chunk_alloc(size_t size, int &nobjs)
	{
		char * result = NULL;
		size_t total_bytes = size * nobjs;
		size_t bytes_left = end_free - start_free;/*当前池子还剩多少内存*/
		if (bytes_left >= total_bytes)/*如果有那么大最好*/
		{
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		else if (bytes_left >= size) /*没有那么大我就退而求其次，只要能申请到就好*/
		{
			nobjs = bytes_left / size;
			total_bytes = size*nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		else/*最基本的内存都申请不到就需要malloc了*/
		{
			/*每次申请都会参考当前heap中的内存大小，需要的越多分配的越多*/
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
			/*当前如果还剩的有内存就给一个合适的free list因为每个free都是8的倍数，所以一定有合适的free list*/
			if (bytes_left > 0)
			{
				obj * volatile * my_free_list = free_list + FREELIST_INDEX(bytes_left);
				((obj*)start_free)->free_list_link = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			/*配置heap空间，补充内存池*/
			start_free = (char*)malloc(bytes_to_get);
			if (NULL == start_free)
			{
				int i;
				obj * volatile * my_free_list,*p;
				/*malloc失败我们还可以在其他free list中找内存*/
				for (i = size; i <= __MAX_BYTES; i += __ALIGN)
				{
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if (NULL != p)
					{
						/*如果某个free list中有内存就切一个chunk给当前free list*/
						*my_free_list = p->free_list_link;//指向下一个chunk
						start_free = (char *)p;
						end_free = start_free + i;
						/*找到了一点内存，递归调用*/
						return chunk_alloc(size, nobjs);
					}
				}
				/*如果free list都没有内存了，就调用一级配置器看out-of-memory机制能否尽点力释放点内存*/
				start_free = (char*)malloc_alloc::allocate(bytes_to_get);
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return chunk_alloc(size, nobjs);
		}
	}
	/*free list中的chunk不够了调用这个填充函数*/
	static void *refill(size_t n) // 16
	{
		int nobjs = 20;//默认20个chunk
		char * chunk = chunk_alloc(n, nobjs);
		obj * result = NULL;
		obj * current_obj, *next_obj;
		int i;
		/*如果只分配了一个chunk那么直接返回*/
		if (nobjs == 1)
			return chunk;
		/*分配了多个就需要把后面的chunk串起来*/
		obj * volatile * my_free_list = free_list + FREELIST_INDEX(n);
		result = (obj*)chunk;
		*my_free_list = next_obj = (obj*)(chunk + n);
		for (i = 1;; ++i)
		{
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + n);
			if (i == nobjs - 1)
			{
				current_obj->free_list_link = NULL;
				break;
			}
			current_obj->free_list_link = next_obj;
		}
		return result;
	}
public:
	/*空间配置函数*/
	static void *allocate(size_t n)// n // 20
	{
		obj * volatile * my_free_list = NULL;
		obj * result = NULL;
		/*大于128调用一级配置器*/
		if (n > (size_t)__MAX_BYTES)
		{
			return malloc_alloc::allocate(n);
		}
		/*寻址16个free list中最合适的一个*/
		my_free_list = free_list + FREELIST_INDEX(n);
		result = *my_free_list;
		if (NULL == result)
		{
			/*当前free list没有chunk，填充这个free list*/
			void *r = refill(ROUND_UP(n));
			return r;
		}
		*my_free_list = result->free_list_link;//当前free list的第一个chunk将要分配出去，所以指向下一个chunk
		return result;
	}
	/*空间释放函数*/
	static void deallocate(void *p, size_t n)
	{
		obj * volatile * my_free_list = NULL;
		obj * q = (obj*)p;
		/*大于128调用一级配置器释放(其实就是直接free掉)*/
		if (n > (size_t)__MAX_BYTES)
		{
			malloc_alloc::deallocate(p, n);
			return;
		}
		/*找到对应的free list把当前归还的chunk进行头插法*/
		my_free_list = free_list + FREELIST_INDEX(n);
		q->free_list_link = *my_free_list;
		*my_free_list = q;
	}
	/*调整内存大小*/
	static void *reallocate(void *p, size_t old_sz, size_t new_sz)
	{
		void *  result;
		size_t copy_sz;

		if (old_sz > (size_t)__MAX_BYTES && new_sz > (size_t)__MAX_BYTES)
		{
			return(malloc_alloc::reallocate(p, old_sz, new_sz));
		}
		if (ROUND_UP(old_sz) == ROUNDP_UP(new_sz))
			return(p);
		result = allocate(new_sz);
		copy_sz = new_sz > old_sz ? old_sz : new_sz;
		memcpy(result, p, copy_sz);
		deallocate(p, old_sz);
		return(result);
	}

};
template<bool threads, int inst>
typename __default_malloc_template<threads, inst>::obj * volatile
	__default_malloc_template<threads, inst>::free_list[__NFREELISTS] = { NULL };

template<bool threads, int inst>
char * __default_malloc_template<threads, inst>::start_free = NULL;

template<bool threads, int inst>
char * __default_malloc_template<threads, inst>::end_free = NULL;

template<bool threads, int inst>
size_t __default_malloc_template<threads, inst>::heap_size = 0;

/*配置器标准接口*/
#ifdef __USE_MALLOC
	typedef __malloc_alloc_template<0> malloc_alloc;
	typedef malloc_alloc alloc;
#else
	typedef __default_malloc_template<0, 0> alloc;//默认使用二级配置器
#endif

template<class T, class Alloc>
class simple_alloc
{
public:
	static T * allocate(size_t n)	 // new []
	{
		return n == 0 ? NULL : (T*)Alloc::allocate(n * sizeof(T));
	}
	static T * allocate()			// new
	{
		return (T*)Alloc::allocate(sizeof(T)); 
	}
	static void deallocate(void *p, size_t n)//delete[]
	{
		if (n == 0) return;
		Alloc::deallocate(p, n*sizeof(T));	
	}
	static void deallocate(void *p)			//delete
	{
		Alloc::deallocate(p, sizeof(T));
	}
};

};

#endif