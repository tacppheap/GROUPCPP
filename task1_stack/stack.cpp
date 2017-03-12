//--------------------------------------------
//! @file stack.cpp
//! Implements a stack class
//!
//! @author Petrov Mikhail, 2017 
//--------------------------------------------
#include "stack.h"



stack::stack()
{
	size_ = 0;
	size_copy_ = size_;
	poison_int_copy_ = POISON_INT;
	capasity_copy_ = capacity_;

	for (int place_num = 0; place_num < capacity_; place_num++)
	{
		data_[place_num] = POISON_INT;
		data_copy_[place_num] = data_[place_num];
	}
}


stack::~stack()
{
	for (int place_num = 0; place_num < capacity_; place_num++)
	{
		data_[place_num] = POISON_INT;
	}
	size_ = POISON_INT;
	
}

stack::value_type stack::top()
{
	return data_[size_ - 1];
}

bool stack::IsOk()
{
	if (size_ > capacity_)
		return false;

	for (int place_num = 0; place_num < size_; place_num++)
		if (data_[place_num] != data_copy_[place_num])
			return false;

	if (size_ != size_copy_)
		return false;

	if (capacity_ != capasity_copy_)
		return false;

	if (POISON_INT != poison_int_copy_)
		return false;
	return true;;
}

size_t stack::capacity()
{
	return capacity_;
}

size_t stack::size()
{
	return size_;
}

bool stack::push(value_type value)
{
	ASSERT_OK("start_of_stack::push()"); //Entry verification
	if (size_ == capacity_)
		return false;
	data_[size_++] = value;
	data_copy_[size_copy_++] = value;
	ASSERT_OK("end_of_stack::push()"); //Exit verification
	return true;
}

stack::value_type stack::pop()
{
	ASSERT_OK("start_of_stack::pop()"); //Entry verification
	value_type deleted_value = POISON_INT;
	if (size_ == 0 )
		return POISON_INT;
	deleted_value = data_[size_ - 1];
	data_[--size_] = POISON_INT;
	data_copy_[--size_copy_] = poison_int_copy_;
	ASSERT_OK("end_of_stack::pop()"); //Exit verification
	return deleted_value;
}

bool stack::empty()
{
	if (size_ == 0)
		return true;
	else
		return false;
}

void stack::dump(string method_name)
{
	cout << "stack(ERROR) - in method: "<<method_name<<"\n\n{\n\n size_ = "
		<<size_	<<
		"\n\n capacity_ = " 
		<<capacity_ << 
		"\n\n data_["
		<<capacity_<<
		"]:\n\n";
	for (int place_num = 0; place_num < capacity_; place_num++)
	{
		if (data_[place_num] != POISON_INT)
			cout << "	    *       ";
		else 
			cout << "	POISON_INT  ";
		cout << "[" << place_num << "] = " << data_[place_num]<<"\n";
	}

	cout << "{\n\n size_copy_ = "
		<< size_ <<
		"\n\n capacity_copy_ = "
		<< capacity_ <<
		"\n\n data_copy_["
		<< capacity_ <<
		"]:\n\n";
	for (int place_num = 0; place_num < capacity_; place_num++)
	{
		if (data_copy_[place_num] != POISON_INT)
			cout << "	    *       ";
		else
			cout << "	POISON_INT  ";
		cout << "[" << place_num << "] = " << data_[place_num] << "\n";
	};
	cout << "}";

		
}
