// is_move_constructible example
#include <iostream>
#include <type_traits>

struct A { int i; };

int main2() {
	A a;
	a.i = 10;
	A a2(std::move(a));
	std:: cout << a2.i << std::endl;//10

	A a3 = std::move(a);
	std::cout << a3.i << std::endl;//10

	getchar();
	return 0;
}