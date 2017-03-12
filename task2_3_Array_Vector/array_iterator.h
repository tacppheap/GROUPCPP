#pragma once
template <typename T> class array_iterator
{


public:
	typedef const T* const_pointer;
	typedef T* pointer;
	typedef T& reference;

	array_iterator(pointer _element);
	array_iterator(const array_iterator<T>& that);
	pointer element;
	~array_iterator();
	bool operator!=(array_iterator<T> const& that) const;
	array_iterator<T>& operator++(int);
	reference operator*() const;

};
/***********************array_iterator implementation************************/

template <typename T> 
array_iterator<T>::array_iterator(typename array_iterator<T>::pointer _element)
{
	element = _element;
}

template <typename T>
array_iterator<T>::array_iterator(const array_iterator<T>& that)
{
	element = that.element;
}

template <typename T>
bool array_iterator<T>::operator!=(array_iterator<T> const& that) const
{
	return element != that.element;
}

template <typename T>
typename array_iterator<T>::reference array_iterator<T>::operator*() const
{
		return *element;

}

template <typename T>
array_iterator<T>& array_iterator<T>::operator++(int)
{
	++element;
	return *this;
}

template <typename T>
array_iterator<T>::~array_iterator()
{
	element = NULL;
}
