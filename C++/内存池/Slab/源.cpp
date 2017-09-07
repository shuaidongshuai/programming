#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vld.h>
#include "Slabclass.h"
using namespace std;

int main()
{
	SlabAlloction slab(6, 36, 3);//6  9  13.5
	slab.salloc(10);
	slab.salloc(13);
	slab.showSlabClassChunk();

	slab.salloc(13);
	slab.showSlabClassChunk();
	char *str = (char *)slab.salloc(13);
	slab.showSlabClassChunk();
	slab.sfree(str);
	slab.showSlabClassChunk();

	slab.salloc(15);
	slab.showSlabClassChunk();

	SlabAlloction slab2(6, 12, 3);//6  9  13.5


	system("pause");
}