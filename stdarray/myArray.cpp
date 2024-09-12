#pragma once
#include "myarray.hpp"

template<typename T , size_t size>
Array<T,size>::Array() {}

template<typename T, size_t size>
T& Array<T, size>::operator[](int index)const {
	if (index < 0) {
		throw std::out_of_range("element is out of range");
	}
	return arr[index];
}

template<typename T, size_t size>
T& Array<T, size>::at(int index) const {
	if (index >= size || index < 0) {
		throw std::out_of_range("element is out of range");
	}
	return arr[index - 1];
}

template<typename T, size_t size>
T& Array<T, size>::front()const {
	if (size != 0) {
		return arr[0];
	}
	else {
		throw std::out_of_range("element is out of range");
	}
}

template<typename T, size_t size>
T& Array<T, size>::back() const{
	if (size != 0) {
		return arr[size - 1];
	}
	else {
		throw std::out_of_range("element is out of range");
	}
}

template<typename T, size_t size>
T* Array<T, size>::data() const{
	return arr;
}

template<typename T, size_t size>
void Array<T, size>::fill(T value) {
	for (int i = 0; i < size; i++) {
		arr[i] = value;
	}
}
