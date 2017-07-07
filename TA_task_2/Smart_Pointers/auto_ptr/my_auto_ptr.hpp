#pragma once
using  TA::auto_ptr;

template<typename T>
auto_ptr<T>::auto_ptr(pointer&& _pointer = nullptr): pointer_(_pointer)
{
	Arg1Dump(auto_ptr, _pointer);
}

template<typename T>
auto_ptr<T>::~auto_ptr()
{
	Arg0Dump(~auto_ptr)
	delete pointer_;
}

template<typename T>
const auto_ptr<T>& auto_ptr<T>::operator=(auto_ptr<T>& _that)
{
	pointer_ = _that.pointer_;
	_that.pointer_ = nullptr;
	return *this;
}

template<typename T>
const auto_ptr<T>& auto_ptr<T>::operator=(auto_ptr<T>&& _that)
{
	pointer_ = _that.pointer_;
	_that.pointer_ = nullptr;
	return *this;
}

template<typename T>
typename auto_ptr<T>::reference auto_ptr<T>::operator*()
{
	if (pointer_ == NULL)
	{
		throw TA::no_init(__FUNCSIG__);
	}
	return *pointer_;
}

template<typename T>
auto_ptr<T>::operator pointer()
{
	pointer temp_pointer = pointer_;
	pointer_ = nullptr();
	Arg0Dump(operator_pointer())
	return temp_pointer;
}

template<typename T>
void auto_ptr<T>::dump() const 
{
	std::cout << "\n pointer_ = " << pointer_<<"\n";
}


template<typename T>
typename auto_ptr<T>::pointer auto_ptr<T>::operator->()
{
	return pointer_;
}

template<typename T>
auto_ptr<T>::auto_ptr(auto_ptr<T>& _that)
{
	pointer_ = _that.pointer_;
	_that.pointer_ = nullptr;
	Arg1Dump(auto_ptr, &_that)
}

template<typename T>
auto_ptr<T>::auto_ptr(auto_ptr<T>&& _that)
{
	pointer_ = _that.pointer_;
	_that.pointer_ = nullptr;
	Arg1Dump(auto_ptr, &_that)
}






