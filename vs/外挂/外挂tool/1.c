#include<stdio.h.>

_declspec(dllexport) void go()
{
	int *p = (int *)0x82f798;
	*p = -100;

	void(*pp)() = (void(*)())0x1241118;
	pp();
}