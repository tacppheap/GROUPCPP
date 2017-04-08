#pragma once
#include "bit_pointer.h"
template <typename T> class vector_iterator
{
public:
	typedef T* pointer;
	typedef T& reference;

	pointer* element_;
	explicit vector_iterator(pointer* _element);
	vector_iterator(const vector_iterator<T>& _that);
	~vector_iterator();
	bool operator!=(vector_iterator<T> const& _that) const;
	vector_iterator<T> operator++(int);
	reference operator*() const;
};

template <> class vector_iterator<bool>
{
public:


	bit_pointer element_;
	explicit vector_iterator(bit_pointer& _element);
	~vector_iterator();
	bool operator!=(const vector_iterator<bool>& _that);
	vector_iterator<bool> operator++(int);
	bool operator*();
};

/***********************vector_iterator implementation************************/

template <typename T>
vector_iterator<T>::vector_iterator(typename vector_iterator<T>::pointer* _element):element_(_element){}

template <typename T>
vector_iterator<T>::vector_iterator(const vector_iterator<T>& _that)
{
	element_ = _that.element_;
}

template <typename T>
bool vector_iterator<T>::operator!=(vector_iterator<T> const& _that) const
{
	return element_ != _that.element_;
}

template <typename T>
typename vector_iterator<T>::reference vector_iterator<T>::operator*() const
{
	if (*element_ == NULL)
		throw TA::no_init(__FUNCSIG__);
	return **element_;

}

template <typename T>
vector_iterator<T> vector_iterator<T>::operator++(int)
{
	vector_iterator<T> temp(*this);
	++element_;
	return temp;
}

template <typename T>
vector_iterator<T>::~vector_iterator()
{
	element_ = NULL;
}

/**************************************VECTOR_ITERATOR<BOOL>**************************************/

vector_iterator<bool>::vector_iterator(bit_pointer& _element) :element_(_element) {}


bool vector_iterator<bool>::operator!=(const vector_iterator<bool>& _that) 
{
	return element_ != _that.element_;
}

bool vector_iterator<bool>::operator*() 
{

	return *element_;

}

vector_iterator<bool> vector_iterator<bool>::operator++(int)
{
	vector_iterator<bool> temp(*this);
	++element_;
	return temp;
}

vector_iterator<bool>::~vector_iterator()
{
	
}