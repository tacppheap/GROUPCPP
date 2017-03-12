#pragma once
template <typename T> class vector_iterator
{


public:
	typedef T* pointer;
	typedef T& reference;

	vector_iterator(pointer* _element);
	vector_iterator(const vector_iterator<T>& that);
	pointer* element;
	~vector_iterator();
	bool operator!=(vector_iterator<T> const& that) const;
	vector_iterator<T>& operator++(int);
	reference operator*() const;

};
/***********************vector_iterator implementation************************/

template <typename T>
vector_iterator<T>::vector_iterator(typename vector_iterator<T>::pointer* _element)
{
	element = _element;
}

template <typename T>
vector_iterator<T>::vector_iterator(const vector_iterator<T>& that)
{
	element = that.element;
}

template <typename T>
bool vector_iterator<T>::operator!=(vector_iterator<T> const& that) const
{
	return element != that.element;
}

template <typename T>
typename vector_iterator<T>::reference vector_iterator<T>::operator*() const
{
	if (*element == NULL)
		throw 0;
	return **element;

}

template <typename T>
vector_iterator<T>& vector_iterator<T>::operator++(int)
{
	++element;
	return *this;
}

template <typename T>
vector_iterator<T>::~vector_iterator()
{

}