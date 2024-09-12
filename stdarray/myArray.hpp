#pragma once

template <typename T, size_t size>
class Array {

public:
	Array();

	T& operator[](int index);
	T& at(int index);

	T& front();
	T& back();
	T* data() const;

	bool empty() const;

	int max_size()const;
	//as i understood max_size() and size() returns same value, so i kept only one of them

	void fill(T value);

private:
	T arr[size];
};
