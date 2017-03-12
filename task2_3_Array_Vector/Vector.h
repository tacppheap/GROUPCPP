#pragma once
#include <iostream>
#include <stdexcept>
#include "my_new.h"
#include "vector_iterator.h"
#define Arg1Dump(name, arg1)\
			cout<<"\n"<<this<<":   "<<#name<<"("<<arg1<<"):\n";\
			dump();

#define Arg2Dump(name, arg1, arg2)\
			cout<<"\n"<<this<<":   "<<#name<<"("<<arg1<<","<<arg2<<"):\n";\
			dump();


using namespace std;

template<typename value_type> class Vector
{
public:
	typedef value_type& reference;
	typedef value_type* pointer;
	typedef const value_type& const_reference;
	typedef const value_type* const_pointer;
	typedef vector_iterator<value_type> iterator;

	iterator begin();
	iterator end();
	pointer** get_data();
	void swap(Vector& _victim);
	reference operator[] (int _position);
	const Vector& operator= (const Vector& _Vector);
	reference first();
	reference last();
	reference at(size_t _position);
	const_reference at(size_t _position) const;
	void erase(int _position);
	void insert(int _position, const_reference _value);
	bool empty();
	const size_t& size() const;
	const size_t& capacity() const;
	explicit Vector(size_t _capacity);
	Vector(const Vector<value_type>& _Vector);
	~Vector();

private:
	pointer* data_;
	size_t capacity_;
	size_t size_;

	const bool IsInRange(int _position) const;
	void delete_element(size_t _position);
	reference get_element(size_t _position);
	const_reference get_element(size_t _position) const;
	void dump();
	void* operator new(size_t _size, void* _where_to_create);
};


/***********************Vector implementation***********************/



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
typename Vector<value_type>::pointer**  Vector<value_type>::get_data()
{
	return &data_;
}

template<typename value_type>
void  Vector<value_type>::swap(Vector& _victim)
{
	size_ = _victim.size();
	capacity_ = _victim.capacity();
	pointer* _rubbish = data_;
	data_ = *_victim.get_data();
	*_victim.get_data() = _rubbish;

}



template<typename value_type>
const bool  Vector<value_type>::IsInRange(int _position) const
{
	return ((_position < capacity_) && (_position >= 0));
}

template<typename value_type>
void Vector<value_type>::delete_element(size_t _position)
{
	if (!IsInRange(_position))
		throw out_of_range("ERROR");

	printf("Try to delete element [%i] with address: %X \n", _position, data_[_position]);

	if (data_[_position] == NULL)
	{
		cout << "element[" << _position << "] not declared, so nothing to delete\n\n";
		return;
	}

	delete data_[_position];
	data_[_position] = NULL;
	size_--;
	cout << "element deleted\n\n";
}


template<typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>::get_element(size_t _position) const
{
	if (!IsInRange(_position))
		throw out_of_range("ERROR");

	if (data_[_position] == NULL)
		throw 0;

	return *data_[_position];
}

template<typename value_type>
typename Vector<value_type>::reference Vector<value_type>::get_element(size_t _position)
{
	return const_cast<reference>(static_cast<const Vector&>(*this).get_element(_position));
}

template<typename value_type>
void  Vector<value_type>::dump()
{
	cout << "\nsize_  = " << size_ << "\ncapacity_ = " << capacity_ << "\ndata_[]= " << data_ << "\n";
	for (int i = 0; i < capacity_; i++)
	{
		if (data_[i] != NULL)
		{
			cout << "	    *       "<<"["<<i<<"] =   "<< *data_[i];
		}
		else
			cout << "	  NULL               ";
		printf("    [%i] = %X\n", i, data_[i]);
	}
}

template<typename value_type>
void*  Vector<value_type>::operator new(size_t _size, void* _where_to_create)
{
	return _where_to_create;
}

template<typename value_type>
typename Vector<value_type>::reference Vector<value_type>:: operator[](int _position)
{
	return get_element(_position);
}

template<typename value_type>
const Vector<value_type>& Vector<value_type>::operator=(const Vector& _that)
{
	cout << "\n\noperator=  \n\n";
	if (_that.capacity() != capacity_)
		throw 0;

	if (&_that == this)
		return *this;

	Vector<value_type> _victim(_that);
	swap(_victim);
	cout << this << " after swap:\n";
	dump();

	cout << &_victim << " after swap:\n";
	_victim.dump();

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
}

template<typename value_type>
typename Vector<value_type>::const_reference Vector<value_type>::at(size_t _position) const
{
	return get_element(_position);
}

template<typename value_type>
void Vector<value_type>::erase(int _position)
{
	delete_element(_position);
	Arg1Dump(erase, _position)
}

template<typename value_type>
void Vector<value_type>::insert(int _position, const_reference _value)
{
	if (data_[_position] == NULL)
	{
		data_[_position] = new value_type(_value);
		size_++;
		Arg2Dump(insert, _position, _value);
		return;
	}
	*data_[_position] = _value;
	Arg2Dump(insert, _position, _value);
}

template<typename value_type>
bool Vector<value_type>::empty()
{
	if (size_ != 0)
		return false;
	return true;
}

template<typename value_type>
const size_t& Vector<value_type>::size() const
{
	return size_;
}

template<typename value_type>
const size_t&  Vector<value_type>::capacity() const
{
	return capacity_;
}



template<typename value_type>
Vector<value_type>::Vector(size_t _capacity)
{
	size_ = 0;
	capacity_ = _capacity;
	data_ = new(0) pointer[_capacity];
	Arg1Dump(Vector, _capacity);
	cout << "New Vector created at adrress:" << this << "\n\n";
}

template<typename value_type>
Vector<value_type>::Vector(const Vector<value_type>& _that)
{

	size_ = _that.size();
	capacity_ = _that.capacity();
	data_ = new pointer[capacity_];
	for (int i = 0; i < capacity_; i++)
	{
		try
		{
			data_[i] = new value_type(_that.at(i));
		}
		catch (int error)
		{
			data_[i] = NULL;
		}
	}
	Arg1Dump(Vector, &_that)
		cout << "New Vector created at adrress:" << this << "\n\n";

}

template<typename value_type>
Vector<value_type>::~Vector()
{
	cout << "Destructor of vector with adress: " << this << "\n";
	for (int i = 0; i < capacity_; i++)
		delete_element(i);
	size_ = NULL;
	capacity_ = NULL;
}