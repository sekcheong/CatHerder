#include <iostream>
#include "debug.h"

void test() {
	cat::debug d("test");
	//d.info("Hello from test!");
	d.info("call from test()");
}

int main() {
	cat::debug d;
	//std::cout << "test debug main!" << std::endl;
	d.info("Hello %s", "World!");
	d.warn("Warning!!");
	d.error("Error!");
	
	test();

	d.die(":(");
	//test();
	//printf("hello %s\n", "world!");
	//m_printf("hello %s\n", "world!");
	return 0;
}