/*
哈希查找是通过计算数据元素的存储地址进行查找的一种方法。O(1)的查找，即所谓的秒杀。哈希查找的本质是先将数据映射成它的哈希值。哈希查找的核心是构造一个哈希函数，它将原来直观、整洁的数据映射为看上去似乎是随机的一些整数。
哈希查找的操作步骤：

1)       用给定的哈希函数构造哈希表；

2)       根据选择的冲突处理方法解决地址冲突；

3)       在哈希表的基础上执行哈希查找。

其实常用的做哈希的手法有“五种”：

第一种：”直接定址法“。

很容易理解，key=Value+C；这个“C"是常量。Value+C其实就是一个简单的哈希函数。

第二种：“除法取余法”。

很容易理解， key=value%C;

(1)   开放地址法　　(有问题，当一个数被删除的时候，再次查找，查找不到后面的数，可能查找的数在后面)  不应该被用 

如果两个数据元素的哈希值相同，则在哈希表中为后插入的数据元素另外选择一个表项。当程序查找哈希表时，如果没有在第一个对应的哈希表项中找到符合查找要求的数据元素，程序就会继续往后查找，直到找到一个符合查找要求的数据元素，或者遇到一个空的表项。　　

(2)   链地址法		(请看hash查找2.cpp)

将哈希值相同的数据元素存放在一个链表中，在查找哈希表的过程中，当查找到这个链表时，必须采用线性查找方法。
*/

//实现哈希函数为“除法取余法”，解决冲突为“开放地址线性探测法”，代码如下：
#include <iostream>
#include <cstring>
#include <assert.h>
using namespace std;


//插入hash表中
template<class T>
int InsertHash(T *hashTable, int hashLen, T data)
{
	int addr = data % hashLen;
	int i = 0;
	//解决冲突
	while (hashTable[addr] && i++ < hashLen)
	{
		if(hashTable[addr] == data)
			return -1;
		addr = ++addr % hashLen;
	}
	if (addr < hashLen)
	{
		hashTable[addr] = data;
		return addr;
	}
	return -1;
}
//找值 
template<class T>
int FindInHashTable(T *hashTable, int hashLen, T data)
{
	int addr = data % hashLen;
	int i = 0;
	while (hashTable[addr] != data && i++ < hashLen)
	{
		addr = ++addr % hashLen;
	}
	if (addr < hashLen)
	{
		hashTable[addr] = data;
		return addr;
	}
	return -1;
}

int main()
{
	int len = 10;//长度 
	int *hashTable = new int[len];//哈希表
	memset(hashTable, 0, sizeof(int) * len);

	int arr[] = { 11, 2, 31, 5, 21, };
	for (int i = 0; i<sizeof(arr) / sizeof(arr[0]); i++)
	{
		InsertHash<int>(hashTable, len, arr[i]);
	}

	cout << FindInHashTable<int>(hashTable, len, 11) << endl;
	cout << FindInHashTable<int>(hashTable, len, 21) << endl;
}

