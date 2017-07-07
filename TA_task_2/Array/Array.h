#pragma once
#include "my_new.h"
#include <iostream>
#include "array_iterator.h"
#include "debug_tools.h"
#include "poison_value.h"		


template<typename value_type, size_t size> class Array
{	
public:
	typedef value_type& reference;
	typedef value_type* pointer;
	typedef const value_type& const_reference;
	typedef const value_type* const_pointer;
	typedef array_iterator<value_type> iterator;
	
	Array();
	Array(const std::initializer_list<value_type>& _list);
	Array(const Array<value_type, size>& _that);
	~Array();
	const Array& operator= (const Array<value_type, size>& _that);
	reference operator[] (size_t _position);
	reference at(size_t _position);
	const_reference at(size_t _position) const;
	void fill(const_reference _value);
	size_t get_size() const;
	reference first();
	reference last();
	bool empty();
	iterator begin();
	iterator end();
	void dump();
	

private:
	size_t size_;
	value_type data_[size];
	const bool IsInRange(size_t _position) const;
	reference get_element(size_t _position);
	const_reference get_element(size_t _position) const;
	void* operator new(size_t _size, void* _where_to_create);
};


#include "Array.hpp"
