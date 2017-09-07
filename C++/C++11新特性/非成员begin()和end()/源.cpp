#include<iostream>
#include<vector>
#include<array>

void test1()
{
	int arr[] = { 2, 3, 4, 5, 6 };
	std::for_each(&arr[0], &arr[0] + sizeof(arr) / sizeof(arr[0]), [](int n) {std::cout << n << " "; });
	std::cout << std::endl;

	auto is_odd = [](int n) {return n % 2 == 1; };
	auto begin = &arr[0];
	auto end = &arr[0] + sizeof(arr) / sizeof(arr[0]);
	auto pos = std::find_if(begin, end, is_odd);
	if (pos != end)
		std::cout << *pos << std::endl;
}

//如果使用非成员的begin()和end()来实现，就会是以下这样的：

void test2()
{
	int arr[] = { 2, 3, 4, 5, 6 };
	std::for_each(std::begin(arr), std::end(arr), [](int n) {std::cout << n << " "; });
	auto is_odd = [](int n) {return n % 2 == 1; };
	auto pos = std::find_if(std::begin(arr), std::end(arr), is_odd);
	if (pos != std::end(arr))
		std::cout << *pos << std::endl;
}

template <typename Iterator>
void bar(Iterator begin, Iterator end)
{
	std::for_each(begin, end, [](int n) {std::cout << n << std::endl; });
	auto is_odd = [](int n) {return n % 2 == 1; };
	auto pos = std::find_if(begin, end, is_odd);
	if (pos != end)
		std::cout << *pos << std::endl;
}
template <typename C>
void foo(C c)
{
	bar(std::begin(c), std::end(c));
}
template <typename T, size_t N>
void foo(T(&arr)[N])
{
	bar(std::begin(arr), std::end(arr));
}
void test3()
{
	int arr[] = { 1, 2, 3 };
	foo(arr);				//调用的是void foo(T(&arr)[N])
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	foo(v);					//调用的是void foo(C c)
}

int main()
{
	//test1();
	//test2();
	test3();

	system("pause");
}