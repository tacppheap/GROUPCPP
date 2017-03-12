#pragma once
#include "my_new.h"
#include <iostream>
#include <stdexcept>
#include "array_iterator.h"
#define Arg1Dump(name, arg1)\
			cout<<"\n"<<this<<":   "<<#name<<"("<<arg1<<"):\n";\
			dump();

#define Arg2Dump(name, arg1, arg2)\
			cout<<"\n"<<this<<":   "<<#name<<"("<<arg1<<","<<arg2<<"):\n";\
			dump();			

using namespace std;

template<typename value_type, size_t size> class Array
{	
public:
	typedef value_type& reference;
	typedef value_type* pointer;
	typedef const value_type& const_reference;
	typedef const value_type* const_pointer;
	typedef array_iterator<value_type> iterator;
	
	void fill(const_reference _value);
	iterator begin();
	iterator end();
	pointer get_data();
	const_pointer get_data() const;
	reference operator[] (int _position);
	const Array& operator= (const Array& _array);
	const size_t& get_size() const;
	reference first();
	reference last();
	reference at(size_t _position);
	const_reference at(size_t _position) const;
	bool empty();
	Array();
	Array(const Array<value_type, size>& _array);
	~Array();

private:
	value_type data_[size];
	size_t size_;
	const bool IsInRange(int _position) const;
	reference get_element(size_t _position);
	const_reference get_element(size_t _position) const;
	void dump();
	void* operator new(size_t _size, void* _where_to_create);
};


/***********************Array implementation***********************/


template<typename value_type, size_t size>
void Array<value_type, size>::fill(typename Array<value_type, size>::const_reference _value)
{
	for (int i = 0; i < size_; i++)
	{
		data_[i] = _value;
	}
	Arg1Dump(fill, _value)
}


template<typename value_type, size_t size>
typename Array<value_type, size>::iterator Array<value_type, size>::begin() 
{
	return iterator(data_);
}


template<typename value_type, size_t size>
typename Array<value_type, size>::iterator Array<value_type, size>::end() 
{
	return iterator(data_ + size_);
}

template<typename value_type, size_t size>
typename Array<value_type, size>::pointer  Array<value_type, size>::get_data() 
{
	return data_;
}

template<typename value_type, size_t size> 
typename Array<value_type, size>::const_pointer  Array<value_type, size>::get_data() const
{
	return data_;
}


template<typename value_type, size_t size>
const bool  Array<value_type, size>::IsInRange(int _position) const
{
	return ((_position < size_) && (_position >= 0));
}

template<typename value_type, size_t size>
typename Array<value_type, size>::const_reference Array<value_type, size>::get_element(size_t _position) const
{
	if (!IsInRange(_position))
		throw out_of_range("ERROR");

	return data_[_position];
}

template<typename value_type, size_t size>
typename Array<value_type, size>::reference Array<value_type, size>::get_element(size_t _position)
{
	return const_cast<reference>(static_cast<const Array&>(*this).get_element(_position));
}

template<typename value_type, size_t size>
void  Array<value_type, size>::dump()
{
	cout <<"\nsize_  = " << size_  << "\ndata_[]= "<< data_<<"\n";
	for (int i = 0; i < size_; i++)
	{
		if (data_[i] != NULL)
		{
			cout << "	    *       ";
			printf("[%i] = %i    ", i, data_[i]);
		}
		else
		{
			cout << "	  NULL      ";
			printf("[%i] = %i    ", i, data_[i]);
		}
		printf("[%i] = %X\n", i, data_+ i);
	}
}

template<typename value_type, size_t size>
void*  Array<value_type, size>::operator new(size_t _size, void* _where_to_create)
{
	return _where_to_create;
}

template<typename value_type, size_t size>
typename Array<value_type, size>::reference Array<value_type, size>:: operator[](int _position)
{
	return get_element(_position);
}

template<typename value_type, size_t size>
const Array<value_type, size>& Array<value_type, size>::operator=(const Array& that)
{
	if (&that == this) 
		return *this;

	this->~Array();
	new(this) Array(that);	
}


template<typename value_type, size_t size>
typename Array<value_type, size>::reference Array<value_type, size>::first()
{
	return get_element(0);
}
template<typename value_type, size_t size>
typename Array<value_type, size>::reference Array<value_type, size>::last()
{
	return get_element(size_ - 1);
}

template<typename value_type, size_t size>
typename Array<value_type, size>::reference Array<value_type, size>::at(size_t _position)
{
	return const_cast<reference>(static_cast<const Array&>(*this).at(_position));
}

template<typename value_type, size_t size>
typename Array<value_type, size>::const_reference Array<value_type, size>::at(size_t _position) const
{
		return get_element(_position);
}

template<typename value_type, size_t size>
bool Array<value_type, size>::empty()
{
	if (size != 0)
		return false;
	return true;
}

template<typename value_type, size_t size>
const size_t& Array<value_type, size>::get_size() const
{
	return size_;
}


template<typename value_type, size_t size>
Array<value_type, size>::Array()
{
	size_ = size;
	Arg1Dump(Array, "");
	cout << "New array created at adrress:" << this << "\n\n";
}

template<typename value_type, size_t size>
Array<value_type, size>::Array(const Array<value_type, size>& _that)
{
	if (size_ != _that.get_size())
		throw 0;
	memcpy(data_, _that.get_data(), size * sizeof(value_type));
	Arg1Dump(Array, &_that);
	cout << "New array created at adrress:" << this << "\n\n";

}

template<typename value_type, size_t size>
Array<value_type, size>::~Array()
{
	cout << "Destructor of array with adress: "<< this<< "\n";
}
