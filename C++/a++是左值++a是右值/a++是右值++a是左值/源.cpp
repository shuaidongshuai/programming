#include<iostream>
using namespace std;

int main()
{
	int a = 1;
	//00C93ABE  mov         dword ptr [a],1 
	int b = ++a + 10;
	/*
	00C93AC5  mov         eax,dword ptr [a]		
	00C93AC8  add         eax,1  
	00C93ACB  mov         dword ptr [a],eax		马上给 a + 1 然后在进行运算
	00C93ACE  mov         ecx,dword ptr [a]  
	00C93AD1  add         ecx,0Ah  
	00C93AD4  mov         dword ptr [b],ecx */
	int c = a++ + 10;
	/*
	00C93AD7  mov         eax,dword ptr [a]		把 a 放到 eax寄存器中  占时用 eax 中的值代替a
	00C93ADA  add         eax,0Ah
	00C93ADD  mov         dword ptr [c],eax
	00C93AE0  mov         ecx,dword ptr [a]
	00C93AE3  add         ecx,1
	00C93AE6  mov         dword ptr [a],ecx		最后才给 a + 1
	*/

	//从上面情况，我们就能总结出来
	// a++ = 10 //这样是错误的，因为a++是左值 把 a 放到了eax 中，eax中寸的是一个数，数是一个右值
	a++ + 10;	//这样是可以的。eax 没有作为左值，只是往里面加 1 了
	cout << a << endl;

	system("pause");
}