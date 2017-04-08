#pragma once
#include "my_new.h"
#include "vector_iterator.h"
#include "my_exceptions.h"
#include "poison_value.h"
#include "debug_tools.h"
#include <algorithm>
#include "bit_pointer.h"

template<typename value_type> class Vector
{
public:
	typedef value_type& reference;
	typedef value_type* pointer;
	typedef const value_type& const_reference;
	typedef const value_type* const_pointer;
	typedef vector_iterator<value_type> iterator;

	Vector();
	explicit Vector(size_t _capacity);
	Vector(const std::initializer_list<value_type>& _list);
	Vector(const Vector<value_type>& _that);
	Vector(Vector<value_type>&& _that);
	~Vector();
	const Vector& operator= (const Vector& _that);
	reference operator[] (size_t _position);
	const_reference operator[] (size_t _position) const;
	reference at(size_t _position);
	const_reference at(size_t _position) const;
	void erase(size_t _position);
	void insert(size_t _position, const_reference _value);
	void push_back(const_reference _value);
	void clear();
	reference first();
	reference last();
	bool empty();
	size_t size() const;
	size_t capacity() const;
	iterator begin();
	iterator end();
	void dump() const;
	

private:
	pointer* data_;
	size_t capacity_;
	size_t size_;
	void realloc(size_t _new_capacity);
	bool IsValid() const;
	void swap(Vector<value_type>&& _victim);
    bool IsInRange(size_t _position) const;
	void delete_element(size_t _position);
	reference get_element(size_t _position);
	const_reference get_element(size_t _position) const;
};

/******************************** VECTOR<BOOL>***********************************/


template<> class Vector<bool>
{
	
	typedef unsigned char bit_store;
	typedef vector_iterator<bool> iterator;
	
public:
	const size_t bit_store_size_ = 8;

	Vector() noexcept;
	explicit Vector(size_t _capacity);
	Vector(const std::initializer_list<bool>& _list);
	Vector(const Vector<bool>& _that);
	~Vector();
	const Vector<bool>& operator= (const Vector<bool>& _that);
	bit_pointer operator[] (int _position);
	const bit_pointer operator[] (int _position) const;
	size_t capacity() const;
	void push_back(bool _value);
	iterator begin();
	iterator end();
	

private:
	bit_store* data_;
	size_t alloc_bytes_amount_;
	size_t capacity_;

	bool IsValid() const;
	bool IsInRange(size_t _position) const;
	void realloc(size_t _new_capacity);
	void swap(Vector<bool>&& _victim);
	void dump() const;
};

#include "Vector.hpp"