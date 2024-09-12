#pragma once
#include <iostream>
#include "myarray.hpp"
using namespace std;

int main() {
	Array<int, 15>a;
	a.fill(1);
	a[0] = 2;
	a[14] = 3;
	cout << a.front() << " " << a.back() << endl;
	a.at(2) = 5;
	cout << a[2] << endl;
	cout << a.at(16) << endl;
	cout << a[7] << endl;
	return 0;
}