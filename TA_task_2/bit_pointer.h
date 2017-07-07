#pragma once
#include "poison_value.h"
class bit_pointer
{
	typedef unsigned char bit_store;

public:
	const size_t bit_store_size_ = sizeof(bit_store) * 8;

	bit_pointer(bit_store* _byte_pointer, size_t bit_pos);
	~bit_pointer();
	const bit_pointer& operator=(bool _value);
	bit_pointer& operator++();
	operator bool() const;
	bool operator!=(const bit_pointer& _that);
	bool operator*();
private:
	bit_store* byte_pointer_;
	size_t bit_pos_;
	const bool get_bit() const;
	void set_bit(bit_store _value);
};

