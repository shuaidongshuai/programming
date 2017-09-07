#include<iostream>
using namespace std;

//NumberParseException是自定义的异常类
class NumberParseException {};

void test1()							// 可能抛出任何异常
{
	char *str1 = "1", *str2 = NULL;
	if (str2 == NULL)
		throw NumberParseException();

	int num1 = atoi(str1);
	int num2 = atoi(str2);//当str2 == NULL 会抛异常
	printf("sum is %d\n", num1 + num2);
}

//表示test2()只能抛出两个异常int , char, 以及这些类型派生的异常，但不会抛出其他异常。
//如果f函数违反了这个规定，抛出了int , char之外的异常, 例如x4, 那么当函数f抛出x4异常时，
//会转换为一个std::unexpected()调用，默认是调用std::terminate(), 通常是调用abort()。
void test2()throw (int , char)
{
	test1();
}
void test3() throw () // 不会抛出任何异常
{
	throw "test3()异常了";
}

int main()
{
	try{
		test3();//如果这里抛异常了，那么下面的代码将不会被执行
		test2();
	}
	catch (NumberParseException){
		printf("输入不是整数\n");
	}
	catch (int ){
		printf("int 异常\n");
	}
	catch (char* e)
	{
		cout << e << "   char* 异常" << endl;
	}
	catch (...)					//相当于switch中的default   其他异常
	{
		printf("未知异常\n");
	}

	system("pause");
}

	//try {
	//	throw E();
	//}
	//catch (H h) {
	//	//何时我们可以能到这里呢
	//}
	//1.如果H和E是相同的类型

	//2.如果H是E的基类

	//3.如果H和E都是指针类型，而且1或者2对它们所引用的类型成立

	//4.如果H和E都是引用类型，而且1或者2对H所引用的类型成立