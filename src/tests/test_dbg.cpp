#include <iostream>
#include "debug.h"

void test() {
	cat::debug d("test");
	d.info("Hello from test!");
	std::cout << d.get_scope() << std::endl;
}

int main() {
	cat::debug d;
	std::cout << "test debug main!" << std::endl;
	test();
	return 0;
}