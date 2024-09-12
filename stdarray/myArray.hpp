#pragma once
#include <iostream>
using namespace std;

template <typename T, size_t size>
class Array {

public:
	Array();

	T& operator[](int index) const;
	T& at(int index) const;

	T& front() const;
	T& back() const;
	T* data() const;

	void fill(T value);

private:
	T arr[size];
};
