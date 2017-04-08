#pragma once


template<typename value_type, size_t size>
void Array<value_type, size>::fill(typename Array<value_type, size>::const_reference _value)
{
	for (int i = 0; i < size_; i++)
		data_[i] = _value;
	Arg1Dump(fill, _value);
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
const bool  Array<value_type, size>::IsInRange(size_t _position) const
{
	return _position < size_;
}

template<typename value_type, size_t size>
typename Array<value_type, size>::const_reference Array<value_type, size>::get_element(size_t _position) const
{
	if (!IsInRange(_position))
		throw TA::out_of_range(__FUNCSIG__);

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
	std::cout << "\nsize_  = " << size_ << "\ndata_[]= " << data_ << "\n";
	for (int i = 0; i < size_; i++)
	{
		std::cout << "	    *       ";
		printf("[%i] = %i    ", i, data_[i]);
		printf("[%i] = %X\n", i, data_ + i);
	}
}

template<typename value_type, size_t size>
void*  Array<value_type, size>::operator new(size_t _size, void* _where_to_create)
{
	return _where_to_create;
}

template<typename value_type, size_t size>
typename Array<value_type, size>::reference Array<value_type, size>:: operator[](size_t _position)
{
	return get_element(_position);
}

template<typename value_type, size_t size>
const Array<value_type, size>& Array<value_type, size>::operator=(const Array<value_type, size>& _that)
{
	if (&_that == this)
		return *this;

	this->~Array();
	new(this) Array(_that);
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
	return (size == 0) ? true : false;
}

template<typename value_type, size_t size>
size_t Array<value_type, size>::get_size() const
{
	return size_;
}


template<typename value_type, size_t size>
Array<value_type, size>::Array()
{
	size_ = size;
	Arg0Dump(Array);
}


template<typename value_type, size_t size>
Array<value_type, size>::Array(const std::initializer_list<value_type>& _list)
{
	size_ = size;
	int i = 0;
	for (std::initializer_list<value_type>::iterator it = _list.begin(); it != _list.end(); it++)
	{
		if (!IsInRange(i))
			break;
		data_[i++] = *it;
	}
	Arg0Dump(Array);
}


template<typename value_type, size_t size>
Array<value_type, size>::Array(const Array<value_type, size>& _that)
{
	size_ = size;
	for (int i = 0; i < size_; i++)
		data_[i] = _that.data_[i];
	Arg1Dump(Array, &_that);

}

template<typename value_type, size_t size>
Array<value_type, size>::~Array()
{
	Arg0Dump(~Vector)
		size_ = TA::poison<size_t>::value_;

}