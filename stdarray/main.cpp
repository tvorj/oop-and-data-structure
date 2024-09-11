#pragma once
#include <iostream>
#include "array.hpp"
using namespace std;

	template <typename T>
	class Array {
	private:
		T* arr;
		size_t size;

	public:
		Array(size_t tsize) {
			if (tsize < 0) {
				throw std::length_error;
			}
			this->size = tsize;
			arr = new T[size];
		}
		T& operator[](int index) {
			return arr[index];
		}
		T& at(int index) {
			if (index >= size || index < 0) {
				throw std::out_of_range;
			}
			else {
				return arr[index];
			}
		}
		T& front() {
			if (size != 0) {
				return arr[0];
			}
		}
		T& back() {
			if (size != 0) {
				return arr[size - 1];
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

	return 0;
}
