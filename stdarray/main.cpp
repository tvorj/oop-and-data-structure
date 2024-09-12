#pragma once
#include <iostream>
#include "array.hpp"
using namespace std;

template <typename T, int size>
class Array {
private:
	T arr[size];
	//int size;

public:
	Array() = default;
	Array(size_t tsize) {
		if (tsize < 0) {
			throw std::length_error("invalid length");
		}
		this->size = tsize;
	}
	T& operator[](int index) {
		if (index < 0) {
			throw std::out_of_range("element is out of range");
		}
		return arr[index];
	}
	T& at(int index) {
		if (index >= size || index < 0) {
			throw std::out_of_range("element is out of range");
		}
		else {
			return arr[index - 1];
		}
	}
	T& front() {
		if (size != 0) {
			return arr[0];
		}
		else {
			throw std::out_of_range("element is out of range");
		}
	}
	T& back() {
		if (size != 0) {
			return arr[size - 1];
		}
		else {
			throw std::out_of_range("element is out of range");
		}
	}
	T* data() {
		return arr;
	}
	void fill(T value) {
		for (int i = 0; i < size; i++) {
			arr[i] = value;
		}
	}
};

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