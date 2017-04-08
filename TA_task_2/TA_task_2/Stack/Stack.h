#pragma once
#include "Array/Array.h"
#include <iostream>
#include "debug_tools.h"
#include "poison_value.h"	


enum STACK_ERROR
{
	NO_STACK_ERROR,
	STACK_IS_FULL
};

template<typename value_type, size_t capacity> class Stack
{
private:
	Array<value_type, capacity> data_;
	size_t size_;
	size_t capacity_;
public:
	Stack();
	~Stack();
	size_t size();
	size_t get_capacity();
	STACK_ERROR push(const value_type& _value);
	value_type pop();
	const value_type& top();
	bool empty();
	void dump();
};
#include "Stack.hpp"