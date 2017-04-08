#pragma once

template<typename value_type, size_t capacity>
Stack<value_type, capacity>::Stack(): capacity_(capacity), size_(0)
{
	for (int i = 0; i < capacity_; i++)
	{
		data_[i] = TA::poison<value_type>::value_;
	}
	Arg0Dump(Stack);
}

template<typename value_type, size_t capacity>
void Stack<value_type, capacity>::dump()
{
	std::cout <<"\nsize_ = " << size_ 
		 <<"\ncapacity_ = "<< capacity_
		 <<"\ndata_["<< capacity_ <<"]:";
	data_.dump();
}

template<typename value_type, size_t capacity>
size_t Stack<value_type, capacity>::get_capacity()
{
	return capacity_;
}

template<typename value_type, size_t capacity>
size_t Stack<value_type, capacity>::size()
{
	return size_;
}

template<typename value_type, size_t capacity>
STACK_ERROR Stack<value_type, capacity>::push(const value_type& _value)
{
	if (size_ == capacity_)
	{
		Arg1Dump(push, _value);
		std::cout << "Stack is full. No push avaible\n";
		return STACK_IS_FULL;
	}
	data_[size_++] = _value;
	Arg1Dump(push, _value);
	return NO_STACK_ERROR;
}

template<typename value_type, size_t capacity>
value_type Stack<value_type, capacity>::pop()
{
	value_type temp = top();
	if (!empty())
	{
		data_[size_-- - 1] = TA::poison<value_type>::value_;
	}
	Arg0Dump(pop);
	return temp;
}

template<typename value_type, size_t capacity>
bool Stack<value_type, capacity>::empty()
{
	return (size_ == 0) ? true : false;
}

template<typename value_type, size_t capacity>
const value_type& Stack<value_type, capacity>::top()
{
	if (empty())
	{
		std::cout << "\nStack is empty\n";
		return TA::poison<value_type>::value_;
	}

	return data_[size_ - 1];
}

template<typename value_type, size_t capacity>
Stack<value_type, capacity>::~Stack()
{
	Arg0Dump(~Stack);
	capacity_ = TA::poison<size_t>::value_;
	size_ = TA::poison<size_t>::value_;
}





