#pragma once
#include <iostream>
#include "myArray.hpp"

int main() {
	Array<int, 15>a;
	a.fill(1);
	a[0] = 2;
	a[14] = 3;
	std::cout << a.front() << " " << a.back() << std::endl;
	a.at(2) = 5;
	std::cout << a[2] << std::endl;
	/*std::cout << a.at(16) << std::endl;*/
	std::cout << a[7] << std::endl;
	std::cout << a.max_size() << std::endl;
	Array<int, 0>b;
	b.fill(2);
	std::cout << b.front() << " " << b.back() << std::endl;
	return 0;
}