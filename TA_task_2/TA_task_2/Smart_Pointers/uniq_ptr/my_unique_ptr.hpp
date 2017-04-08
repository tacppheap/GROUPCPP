#pragma once

using  TA::unique_ptr;

template<typename T>
unique_ptr<T>::unique_ptr(pointer&& _pointer = nullptr) : pointer_(_pointer)
{
	Arg1Dump(unique_ptr, _pointer);
}

template<typename T>
unique_ptr<T>::~unique_ptr()
{
	Arg0Dump(~unique_ptr)
		delete pointer_;
}


template<typename T>
const unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& _that)
{
	pointer_ = _that.pointer_;
	_that.pointer_ = nullptr;
	return *this;
}

template<typename T>
typename unique_ptr<T>::reference unique_ptr<T>::operator*()
{
	if (pointer_ == NULL)
	{
		throw TA::no_init(__FUNCSIG__);
	}
	return *pointer_;
}



template<typename T>
void unique_ptr<T>::dump() const
{
	std::cout << "\n pointer_ = " << pointer_ << "\n";
}


template<typename T>
typename unique_ptr<T>::pointer unique_ptr<T>::operator->()
{
	return pointer_;
}


template<typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& _that)
{
	pointer_ = _that.pointer_;
	_that.pointer_ = nullptr;
	Arg1Dump(unique_ptr, &_that)
}
