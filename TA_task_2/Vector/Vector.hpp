#pragma once


template<typename value_type>
void Vector<value_type>::clear()
{
	realloc(0);
}

template<typename value_type>
vector_iterator<value_type> Vector<value_type>::begin() 
{
	return vector_iterator<value_type>(data_);
}


template<typename value_type>
vector_iterator<value_type> Vector<value_type>::end() 
{
	return vector_iterator<value_type>(data_ + capacity_);
}



template<typename value_type>
void  Vector<value_type>::swap(Vector<value_type>& _victim)
{
	VALID_ASSERT(this);
	size_t temp_size = size_;
	size_ = _victim.size_;
	_victim.size_ = temp_size;

	size_t temp_capacity = capacity_;
	capacity_ = _victim.capacity_;
	_victim.capacity_ = temp_capacity;

	pointer* _rubbish = data_;
	data_ = _victim.data_;
	_victim.data_ = _rubbish;
	VALID_ASSERT(this);
}

template<typename value_type>
bool  Vector<value_type>::IsInRange(size_t _position) const
{
	return _position < capacity_;
}

template<typename value_type>
void Vector<value_type>::delete_element(size_t _position)
{
	VALID_ASSERT(this);
	if (!IsInRange(_position))
		throw TA::out_of_range(__FUNCSIG__);

	printf("Try to delete element [%i] with address: %X \n", _position, data_[_position]);

	if (data_[_position] == NULL)
	{
		std::cout << "element[" << _position << "] not initialized, so nothing to delete\n\n";
		return;
	}

	delete data_[_position];
	data_[_position] = NULL;
	size_--;
	std::cout << "element deleted\n\n";
	VALID_ASSERT(this);
}


template<typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>::get_element(size_t _position) const
{

	if (!IsInRange(_position))
		throw TA::out_of_range(__FUNCSIG__);

	if (data_[_position] == NULL)
		throw TA::no_init(__FUNCSIG__);

	return *data_[_position];
}

template<typename value_type>
typename Vector<value_type>::reference Vector<value_type>::get_element(size_t _position)
{
	return const_cast<reference>(static_cast<const Vector&>(*this).get_element(_position));
	VALID_ASSERT(this);
}

template<typename value_type>
void  Vector<value_type>::dump() const 
{
	std::cout << "\nsize_  = " << size_ << "\ncapacity_ = " << capacity_ << "\ndata_[]= " << data_ << "\n";

	if (data_ == NULL) 
		return;

	for (int i = 0; i < capacity_; i++)
	{
		if (data_[i] != NULL)
		{
			//std::cout << "	    *       " << "[" << i << "] =   " << *data_[i];
		}
		else
			std::cout << "	  NULL               ";
		printf("    [%i] = %X\n", i, data_[i]);
	}
}

template<typename value_type>
typename Vector<value_type>::reference Vector<value_type>:: operator[](size_t _position)
{
	return get_element(_position);
}

template<typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>:: operator[](size_t _position) const
{
	return get_element(_position);
}

template<typename value_type>
const Vector<value_type>& Vector<value_type>::operator=(const Vector<value_type>& _that)
{
	VALID_ASSERT(this);
	const Vector<value_type>* that_pointer = &_that;
	VALID_ASSERT(that_pointer);
	Arg1Dump(operator=before_swap , &_that)

	if (&_that == this)
		return *this;
	swap(Vector<value_type>(_that));
	Arg1Dump(operator=after_swap, &_that)
	VALID_ASSERT(this);
	return *this;

}


template<typename value_type>
typename Vector<value_type>::reference Vector<value_type>::first()
{
	return get_element(0);
}

template<typename value_type>
typename Vector<value_type>::reference Vector<value_type>::last()
{
	return get_element(capacity_ - 1);
}

template<typename value_type>
typename Vector<value_type>::reference Vector<value_type>::at(size_t _position)
{
	return const_cast<reference>(static_cast<const Vector&>(*this).at(_position));
	VALID_ASSERT(this);
}

template<typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>::at(size_t _position) const
{
	return get_element(_position);
}

template<typename value_type>

void Vector<value_type>::erase(size_t _position)
{
	delete_element(_position);
	Arg1Dump(erase, _position)
}

template<typename value_type>
void Vector<value_type>::insert(size_t _position, const_reference _value)
{
	VALID_ASSERT(this);
	if (!IsInRange(_position))
		throw TA::out_of_range(__FUNCSIG__);

	if (data_[_position] == NULL)
	{
		try
		{
			data_[_position] = new value_type(_value);
		}
		catch (...)
		{
			throw TA::bad_alloc(__FUNCSIG__);
		}
		size_++;
		Arg2Dump(insert, _position, _value);
		VALID_ASSERT(this);
		return;
	}
	*data_[_position] = _value;
	Arg2Dump(insert, _position, _value);
	VALID_ASSERT(this);
}

template<typename value_type>
bool Vector<value_type>::empty()
{
	return (size_ != 0) ? false :
						  true;
}

template<typename value_type>
size_t Vector<value_type>::size() const
{
	return size_;
}

template<typename value_type>
size_t  Vector<value_type>::capacity() const
{
	return capacity_;
}

template<typename value_type>
Vector<value_type>::Vector(size_t _capacity)
{
	size_ = 0;
	capacity_ = _capacity;
	try 
	{
		data_ = new(0) pointer[_capacity];
	}
	catch(...)
	{
		throw;
	}
	Arg1Dump(Vector, _capacity);
	VALID_ASSERT(this);
}

template<typename value_type>
Vector<value_type>::Vector(const Vector<value_type>& _that)
{
	VALID_ASSERT(this);
	const Vector<value_type>* that_pointer = &_that;
	VALID_ASSERT(that_pointer);
	size_ = _that.size();
	capacity_ = _that.capacity();
	try
	{
		data_ = new pointer[capacity_];
	}
	catch (...)
	{
		throw;
	}
	for (int i = 0; i < capacity_; i++)
	{
		try
		{
			data_[i] = new value_type(_that.at(i));
		}
		catch (TA::no_init error)
		{
			data_[i] = NULL;
		}
	}
	Arg1Dump(Vector, &_that)
	VALID_ASSERT(this);

}

template<typename value_type>
Vector<value_type>::Vector(Vector<value_type>&& _that)
{
	VALID_ASSERT(this);
	const Vector<value_type>* that_pointer = &_that;
	VALID_ASSERT(that_pointer);
	this->swap(_that);
	Arg1Dump(Vector, &_that)
	VALID_ASSERT(this);

}

template<typename value_type>
Vector<value_type>::~Vector()
{
	Arg0Dump(~Vector)
	realloc(0);
	data_ = NULL;
	size_ = TA::poison<size_t>::value_;
	capacity_ = TA::poison<size_t>::value_;
}


template<typename value_type>
Vector<value_type>::Vector()
{
	data_ = NULL;
	size_ = 0;
	capacity_ = 0;
	Arg0Dump(Vector);
	VALID_ASSERT(this);
}

template<typename value_type>
Vector<value_type>::Vector(const std::initializer_list<value_type>& _list)
{
	data_ = NULL;
	size_ = 0;
	capacity_ = 0;
	realloc(_list.size());
	int i = 0;
	for (std::initializer_list<value_type>::iterator it = _list.begin(); it != _list.end(); it++)
		data_[i++] = new value_type(*it) ;
	size_ = _list.size();
	Arg0Dump(Vector);
	VALID_ASSERT(this);
}


template<typename value_type>
bool Vector<value_type>::IsValid() const
{
	return data_ == NULL && capacity_ != 0;
}

template<typename value_type>
void Vector<value_type>::realloc(size_t _new_capacity)
{
	VALID_ASSERT(this);
	if (_new_capacity == capacity_)
		return;
	if (_new_capacity >  capacity_)
	{
		pointer* _temp = new(0) pointer[_new_capacity];
		memcpy(_temp, data_, capacity_ * sizeof(pointer));
		delete[] data_;
		data_ = _temp;
		capacity_ = _new_capacity;
	}
	if (_new_capacity < capacity_)
	{
		pointer* _temp = new pointer[_new_capacity];
		memcpy(_temp, data_, _new_capacity * sizeof(pointer));
		for (int i = _new_capacity ; i < capacity_; i++)
			delete_element(i);
		delete[] data_; 
		data_ = _temp;
		capacity_ = _new_capacity;
	}
	VALID_ASSERT(this);
	
}

template<typename value_type>
void Vector<value_type>::push_back(typename Vector<value_type>::const_reference _value)
{
	VALID_ASSERT(this);
	try
	{
		realloc(capacity_ + 1);
		data_[capacity_ - 1] = new value_type(_value);
		size_++;
	}
	catch(...)
	{
		throw TA::bad_alloc(__FUNCSIG__);
	}

	Arg1Dump(push_back, _value);
	VALID_ASSERT(this);


}

Vector<bool>::Vector() noexcept
{
	data_ = nullptr;
	alloc_bytes_amount_ = 0;
	capacity_ = 0;
	Arg0Dump(Vector);
}

Vector<bool>::Vector(size_t _capacity)
{
	data_ = nullptr;
	alloc_bytes_amount_ = 0;
	capacity_ = 0;

	try
	{
		realloc(_capacity);
	}
	catch (...)
	{
		throw;
	}
	VALID_ASSERT(this);
	Arg1Dump(Vector, _capacity)
}

bool Vector<bool>::IsValid() const
{
	return data_ == NULL && capacity_ != 0;
}

bool Vector<bool>::IsInRange(size_t _position) const
{
	return _position < capacity_;
}

void Vector<bool>::realloc(size_t _new_capacity)
{
	VALID_ASSERT(this);
	size_t realloc_bytes_amount = 0;

	if ((_new_capacity % bit_store_size_) == 0)
		realloc_bytes_amount = _new_capacity / bit_store_size_;
	else
		realloc_bytes_amount = _new_capacity / bit_store_size_ + 1;

	if (realloc_bytes_amount == alloc_bytes_amount_)
	{
		capacity_ = _new_capacity;
		Arg1Dump(realloc, _new_capacity);
		VALID_ASSERT(this);
		return;
	}

	bit_store* temp = NULL;

	try 
	{
		temp = new(0) bit_store[realloc_bytes_amount];
		memcpy(temp, data_, std::min(realloc_bytes_amount, alloc_bytes_amount_) * sizeof(bit_store));
	}
	catch(...)
	{
		throw TA::bad_alloc(__FUNCSIG__);
	}
	delete[] data_;
	data_ = temp;
	capacity_ = _new_capacity;
	alloc_bytes_amount_ = realloc_bytes_amount;
	VALID_ASSERT(this);
	Arg1Dump(realloc, _new_capacity)
}


Vector<bool>::~Vector()
{
	Arg0Dump(~Vector);
	delete[] data_;
	alloc_bytes_amount_ = TA::poison<size_t>::value_;
	capacity_ = TA::poison<size_t>::value_;
}

Vector<bool>::Vector(const Vector<bool>& _that)
{
	VALID_ASSERT(this);
	const Vector<bool>* that_pointer = &_that;
	VALID_ASSERT(that_pointer);
	capacity_ = _that.capacity_;
	alloc_bytes_amount_ = _that.alloc_bytes_amount_;
	try
	{
		data_ = new(0) bit_store[capacity_];
	}
	catch (...)
	{
		throw;
	}
	for (int i = 0; i < capacity_; i++)
		this->operator[](i) = (bool)_that[i];
	VALID_ASSERT(this);
	Arg1Dump(Vector, &_that);
}

void Vector<bool>::swap(Vector<bool>&& _victim)
{
	VALID_ASSERT(this);
	size_t temp_bytes_amount = alloc_bytes_amount_;
	alloc_bytes_amount_ = _victim.alloc_bytes_amount_;
	_victim.alloc_bytes_amount_ = temp_bytes_amount;

	size_t temp_capacity = capacity_;
	capacity_ = _victim.capacity_;
	_victim.capacity_ = temp_capacity;

	bit_store* _rubbish = data_;
	data_ = _victim.data_;
	_victim.data_ = _rubbish;
	VALID_ASSERT(this);
	Arg1Dump(swap, &_victim)
}

size_t  Vector<bool>::capacity() const 
{
	return capacity_;
}


bit_pointer Vector<bool>::operator[] (int _position)
{
	if (IsInRange(_position))
		return bit_pointer(&data_[_position / bit_store_size_], _position % bit_store_size_);
	else
		throw TA::out_of_range(__FUNCSIG__);
}

const bit_pointer Vector<bool>::operator[] (int _position) const
{
	return bit_pointer(&data_[_position / bit_store_size_], _position % bit_store_size_);
}

Vector<bool>::Vector(const std::initializer_list<bool>& _list)
{
	VALID_ASSERT(this);
	realloc(_list.size());
	int i = 0;
	for (std::initializer_list<bool>::iterator it = _list.begin(); it != _list.end(); it++)
		this->operator[](i++) = *it;
	VALID_ASSERT(this);
	Arg0Dump(Vector);
}

const Vector<bool>& Vector<bool>::operator= (const Vector<bool>& _that)
{
	VALID_ASSERT(this);

	const Vector<bool>* that_pointer = &_that;
	VALID_ASSERT(that_pointer);

	if (&_that == this)
		return *this;
	swap(Vector<bool>(_that));
	return *this;
	VALID_ASSERT(this);
	Arg1Dump(operator=, &_that);

}

void  Vector<bool>::push_back(bool _value)
{
	VALID_ASSERT(this);
	try
	{
		realloc(capacity_ + 1);
		this->operator[](capacity_ - 1) = _value;
		Arg1Dump(push_back, _value);
		VALID_ASSERT(this);
	}
	catch (...)
	{
		throw TA::bad_alloc(__FUNCSIG__);
	}

}

void  Vector<bool>::dump() const
{
	std::cout << "\nalloc_bytes_amount_  = " << alloc_bytes_amount_ << "\ncapacity_ = " << capacity_ <<"\n";
	printf("data_: %X\n\n", data_);
	if (data_ == NULL)
		return;

	std::cout << "data bits: \n";

	for (int i = 0; i < capacity_; i++)
		std::cout << "	    *       " << "[" << i << "] =   " << this->operator[](i) << "\n";
}


vector_iterator<bool> Vector<bool>::begin()
{
	return vector_iterator<bool>(bit_pointer(&data_[0], 0));
}



vector_iterator<bool> Vector<bool>::end()
{
	size_t temp = (capacity_ % bit_store_size_ == 0) ? 0 : capacity_ % bit_store_size_;

	return vector_iterator<bool>(bit_pointer(&data_[capacity_ / bit_store_size_], temp));
}





