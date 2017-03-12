//--------------------------------------------
//! @file stack.h
//! Implements a stack class
//!
//! @author Petrov Mikhail, 2017 
//--------------------------------------------

#pragma once
#include "assert.h"
#include <string>
#include <iostream>
//--------------------------------------------
//! Macro for silent verification
//--------------------------------------------
#define ASSERT_OK(method_name)\
			if( !IsOk() )\
			{\
				dump(method_name);\
				assert(!"OBJECT IS NOT OK");\
			}
using namespace std;

//---------------------------------------------
//! stack class
//--------------------------------------------

class stack
{
public:
	typedef float value_type;//!< Elems type
	//--------------------------------------------
	//! @return stack size
	//--------------------------------------------
	size_t size();
	//--------------------------------------------
	//! @return stack capacity
	//--------------------------------------------
	size_t capacity();
	//--------------------------------------------
	//! Pushes a value to the stack
	//! @param value is an element to push in
	//! @return success of operation
	//--------------------------------------------
	bool push(value_type value);
	//--------------------------------------------
	//! Remove top element from the stack
	//! @return deleted element
	//--------------------------------------------
	value_type pop();
	//--------------------------------------------
	//! @return top element of the stack
	//--------------------------------------------
	value_type top();
	//--------------------------------------------
	//! @return true if the stack is empty, else false
	//--------------------------------------------
	bool empty();
	stack();
	~stack(); 
private:
	static const int POISON_INT = 666;
	int poison_int_copy_;
	static const size_t capacity_ = 5;
	size_t capasity_copy_;
	size_t size_;
	size_t size_copy_;
	value_type data_ [capacity_];
	value_type data_copy_[capacity_];
	//--------------------------------------------
	//! Silent Verifier
	//--------------------------------------------
	bool IsOk();
	//--------------------------------------------
	//! Dumper
	//--------------------------------------------
	void dump(string method_name);
};

