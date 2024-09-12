#pragma once
#include "myArray.hpp"

template<typename T, size_t size>
Array<T, size>::Array() {}

template<typename T, size_t size>
T& Array<T, size>::operator[](int index) {
	if (index < 0) {
		throw std::out_of_range("element is out of range");
	}
	return arr[index];
}

template<typename T, size_t size>
T& Array<T, size>::at(int index) {
	if (index >= size || index < 0) {
		throw std::out_of_range("element is out of range");
	}
	return arr[index];
}

template<typename T, size_t size>
T& Array<T, size>::front() {
	if (size == 0) {
		throw std::out_of_range("there is no element");
	}
	return arr[0];
}

template<typename T, size_t size>
T& Array<T, size>::back() {
	if (size == 0) {
		throw std::out_of_range("there is no element");
	}
	return arr[size - 1];
}

template<typename T, size_t size>
T* Array<T, size>::data() const {
	return arr;
}

template <typename T, size_t size>
bool Array<T, size>::empty() const {
	if (size != 0) {
		return false;
	}
	return true;
}

template<typename T, size_t size>
int Array<T, size>::max_size() const {
	return size;
}

template<typename T, size_t size>
void Array<T, size>::fill(T value) {
	for (int i = 0; i < size; i++) {
		arr[i] = value;
	}
}
