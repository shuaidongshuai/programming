#include<iostream>
using namespace std;
/*
我们可以把 常量 转化为 常量	  const int -> const int		对
我们可以把 变量 转化为 常量   int -> const int				对
我们可以把 常量 转化为 变量   const int -> int				对	为变量赋一个常量值

							  const int * -> const int *	对
							  int * -> const int *			对 
							  const int * -> int *			错

							  int ** -> const int **		错
							  const int ** -> int **		错
这里的int 可以换成 char long ...  或者 int *  , char *
*/

int main3()
{
	//简单一点说
	int *p = NULL;
	int const *d = p;//d可以更改 类型是：int const *    也就是说可以用 int* -> int const  *
	//int *pppp = d;  const int * -> int *错

	int *const* q = &p;//p == *q  *q不能改变
	int **const q2 = &p;//*q 可以被赋值 可以被 int *赋值    相当于 *p可以被 int * 赋值，，没问题
	cout << typeid(d).name() << endl;
	//int const ** q3 = &p;	//错， *q 可以被赋值 可以被 int const *赋值    相当于 *p可以被 int const * 赋值，那就错了
	const int ** dong = NULL;
	//int ** dong2 = dong;//无法从“const int **”转换为“int **”

	int const *pp;
	int const ** q3 = &pp;//*q 可以被赋值 可以被 int const *赋值    相当于 p可以被 int const * 赋值，没问题
	
	//相反
	const int *a;
	//int **b = &a;  //错，我们可以给*b赋值 类型是： int *  相当于 a 被 int * 赋值，对的
					//但是我们给 a也可以赋值 类型是：const int *  相当于 *b 被 const int * 赋值，错的
					//这里我们多了一个反方向的验证，上面两个例子我们没有反方向证明，但是反方向证明后，也是没问题的，这个例子反方向证明就挂了。
	//所以我们以后需要两个方向同时验证（也可以从const下手，这样一个方向也能解决）
	// 碰见 const int *a  我们就想到：给 *a 赋值（赋不了值）  给 a赋值，然后去验证
	// 碰见 const int **a	给 **a 赋值（赋不了值）	给 *a 赋值，然后去验证  给 a赋值，然后去验证
	//解决方案：
	const int **b = &a;

	//还有一种特殊的
	int *const c = NULL;
	//int **d = &c; //错，当我们给 *d 赋值 int* 类型的值  相当于给 c 赋值 虽然类型可以匹配， 但是c不能被赋值
	//就好像下面这种情况
	int const x = 1;
	int const y = 2;
	//x = y;	x和y类型虽然一样，but x是常量

	//总结:当const右边没有*  我们验证非const的值，当const右边有*，我们验证const   (就是变动那个值）
	//要是记不住，两边都验证
	getchar();
	return 0;
}
int main2()
{
	int *p;
	//const int **q = &p;// 无法从“int **”转换为“const int **” 为什么会这样呢？
						//下面不是说  int -> const int 可行么
	//const int **q表示不能修改**p 的值，，但是我们可以修改*p的值啊（*p 能作为左值）
	//对于 *p来说   const int*  *p;		*p是一个const int* 类型的
	//如果我们令const int *b = NULL;  *p = b;  相当于p = b ;  如果是这样的话，就是 const int -> int	,所以编译器不允许
	
	//解决办法：1
	const int *const *q = &p;//可以	  **q 是一个常量  *q  也是一个常量(换句话说*p 不能作为左值了)
	//解决办法：2
	const int *a;
	const int **b = &a;//这样的话，**b是一个常量（不能作为左值）    *b（可以作为左值）
						//但是  我们令const int *c = NULL;  *b = c;  相当于a = b ;  const int -> cosnt int 没啥问题
	//下面这样搞就没啥问题了
	const int *c = NULL;
	*b = c;
	a = c;


	system("pause");
	return 0;
}
int main1()
{
	int a = 10;
	int &b = a;
	const int c = a;	// int -> const int  可行

	const int Pi = 3; 
	int i = Pi;			// const int -> int 也行
	i = 5;
	cout << i << endl;

	//const int a = 10;
	//const int &b = a;	//	const int -> const int 
	
	system("pause");
	return 0;
}