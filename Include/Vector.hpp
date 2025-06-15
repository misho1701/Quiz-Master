#pragma once
#include "Utils.h"
namespace {


	template<typename F>
	void setValuesToArr(F*& arr, const F& value, size_t size) {

		for (size_t i = 0; i < size; i++) {
			arr[i] = value;
		}
	}

	void swapValues(size_t& a, size_t& b) {
		a = a ^ b;
		b = a ^ b;
		a = a ^ b;
	}
}


template <typename T>
class Vector {
public:

	Vector();
	Vector(size_t size, const T& initialValue);
	Vector(const Vector& vector);
	Vector(size_t capacity);
	Vector& operator=(const Vector& vector);
	~Vector();

	void push_back(const T& value);
	void pop_back();
	bool is_empty() const;
	void reserve(size_t newCapacity);
	void shrink_to_fit();
	void clear();

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	const T& at(size_t index) const;
	T& at(size_t index);

	const T* begin() const;
	T* begin();
	
	const T* end() const;
	T* end();

	void remove_at(size_t index);
	void insert_at(size_t index, const T& value);
	void insert_range(size_t index, const T* values, size_t size);
	void swap(Vector& other);
	void resize(size_t new_size, const T& default_value = T());

	const T* data() const;
	size_t size() const;
	size_t capacity() const;

	bool contains(const T& value) const;

private:
	static const size_t INITIAL_SIZE = 8;

	T* _data;
	size_t _size;
	size_t _capacity;

	void copyDynamic(const Vector& vector);
	void freeDynamic();
	void copy(T*& dest, const T* source, size_t size);

};

template <typename T>
void Vector<T>::copy(T*& dest, const T* source, size_t size) {
	for (size_t i = 0; i < size; i++) {
		dest[i] = source[i];
	}
}

template <typename T>
Vector<T>::Vector(): _size(0), _capacity(INITIAL_SIZE), _data(new T[INITIAL_SIZE])
{
}



template <typename T>
Vector<T>::Vector(size_t size, const T& initialValue) {
	this->_size = size;
	this->_capacity = std::max(roundToPowerOfTwo(this->_size + 1), INITIAL_SIZE);
	this->_data = new T[_capacity];
	setValuesToArr<T>(this->_data, initialValue, size);
}

template <typename T>
Vector<T>::Vector(size_t capacity) {
	this->_data = new T[capacity];
	this->_capacity = capacity;
	this->_size = 0;
}

template< typename T>
Vector<T>::Vector(const Vector& vector) : _capacity(vector.capacity()), _size(vector.size()) {
	copyDynamic(vector);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& vector) {
	if (this != &vector) {
		freeDynamic();
		copyDynamic(vector);
		this->_capacity = vector.capacity();
		this->_size = vector.size();
	}

	return *this;
}

template <typename T>
Vector<T>::~Vector() {
	freeDynamic();
	this->_size = 0;
	this->_capacity = 0;
}


template <typename T>
void Vector<T>::freeDynamic() {
	delete[] this->_data;
}

template <typename T>

bool Vector<T>::is_empty() const {
	return this->_size == 0;
}

template <typename T>
void Vector<T>::copyDynamic(const Vector& vector) {
	this->_data = new T[capacity()];
	copy(this->_data, vector.data(), vector.size());
}

template <typename T>
size_t Vector<T>::size() const {
	return this->_size;
}

template <typename T>
const T* Vector<T>::data() const {
	return this->_data;
}

template <typename T>
size_t Vector<T>::capacity() const {
	return this->_capacity;
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
	return this->_data[index];
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
	return this->_data[index];
}

template <typename T>
void Vector<T>::reserve(size_t newCapacity) {
	if (newCapacity >= this->capacity()) {
		T* temp = new T[newCapacity];
		copy(temp, this->data(), this->size());
		delete[] this->_data;
		this->_data = temp;
		this->_capacity = newCapacity;
	}
}

template <typename T>
void Vector<T>::shrink_to_fit() {
	if (this->size() != this->capacity()) {
		T* temp = new T[_size];
		copy(temp, this->data(), this->size());
		delete[] _data;
		this->_data = temp;
		this->_capacity = this->size();
	}
}

template <typename T>
void Vector<T>::push_back(const T& value) {
	if (this->size() == this->capacity()) {
		reserve(this->capacity() * 2);
	}

	_data[size()] = value;
	_size++;
}

template <typename T>
T& Vector<T>::at(size_t index) {

	if (index < 0 || index > this->size()) {
		throw std::out_of_range("Index out of range");
	}

	return this->_data[index];

}

template <typename T>
const T& Vector<T>::at(size_t index) const {

	if (index < 0 || index > this->size()) {
		throw std::out_of_range("Index out of range");
	}

	return this->_data[index];
}

template <typename T>
void Vector<T>::clear() {

	this->_size = 0;
}


template <typename T>
void Vector<T>::pop_back() {
	if (this->size() == 0) {
		throw std::out_of_range("Could not remove element");
	}

	_size--;

}

template <typename T>
void Vector<T>::remove_at(size_t index) {
	if (index < 0 || index > this->size()) {
		throw std::out_of_range("Index out of range");
	}

	for (size_t i = index; i < this->size() - 1; i++) {
		this->_data[i] = this->_data[i + 1];
	}

	_size--;
}

template <typename T>
void Vector<T>::insert_at(size_t index, const T& value) {
	if (index > this->size()) {
		throw std::out_of_range("Index out of range");
	}

	if (this->size() == this->capacity()) {
		this->reserve(this->capacity() * 2);
	}

	for (size_t ind = this->size(); ind > index; --ind) {
		this->_data[ind] = this->_data[ind - 1];
	}

	this->_data[index] = value;
	_size++;

}

template <typename T>

void Vector<T>::insert_range(size_t index, const T* values, size_t size) {
	if (index < 0 || index > this->size()) {
		throw std::out_of_range("Index out of range");
	}

	if (this->size() + size > this->capacity()) {
		this->reserve(roundToPowerOfTwo(this->size() + size + 1));
	}

	for (int ind = this->size(); ind >= (int)index; ind--) {
		this->_data[ind + size] = this->_data[ind];
	}

	for (size_t i = 0; i < size; i++) {
		this->_data[index + i] = values[i];
	}

	this->_size += size;
}

template <typename T>
void Vector<T>::swap(Vector& other) {

	if (this != &other) {
		T* tempData = this->_data;
		this->_data = other._data;
		other._data = tempData;
		swapValues(this->_size, other._size);
		swapValues(this->_capacity, other._capacity);
	}
	else {
		throw std::invalid_argument("Cannot swap with itself");
	}

}

template<typename T>
void Vector<T>::resize(size_t new_size, const T& default_value)
{
	if (new_size < this->size()) {
		this->_size = new_size;
	}
	else if (new_size > this->capacity()) {
		this->reserve(roundToPowerOfTwo(new_size + 1));
	}

	if (new_size > this->size()) {
		for (size_t i = this->size(); i < new_size; i++) {
			this->_data[i] = default_value;
		}
	}

	this->_size = new_size;
}

template <typename T>
bool Vector<T>::contains(const T& value) const {
	for (size_t i = 0; i < this->size(); i++) {
		if (this->_data[i] == value) {
			return true;
		}
	}
	return false;
}

template <typename T>
const T* Vector<T>::begin() const {
	return this->_data;
}

template <typename T>
T* Vector<T>::begin() {
	return this->_data;
}

template <typename T>
const T* Vector<T>::end() const {
	return this->_data + this->_size;
}

template <typename T>
T* Vector<T>::end() {
	return this->_data + this->_size;
}
