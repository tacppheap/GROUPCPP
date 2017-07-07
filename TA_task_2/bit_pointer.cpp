#include "bit_pointer.h"



bit_pointer::bit_pointer(bit_store* _byte_pointer, size_t _bit_pos): byte_pointer_(_byte_pointer), bit_pos_(_bit_pos)
{
}


bit_pointer::~bit_pointer()
{
	byte_pointer_ = nullptr;
	bit_pos_ = TA::poison<size_t>::value_;
}

const bool bit_pointer::get_bit() const
{
	return !!(*byte_pointer_ & (1 << bit_pos_));
}

void bit_pointer::set_bit(typename bit_pointer::bit_store _value)
{
	bit_store temp = 0b00000001;
	temp &= _value;	

	*byte_pointer_ = (temp) ? *byte_pointer_ |  (1 << bit_pos_) :
	                	      *byte_pointer_ & ~(1 << bit_pos_);
}

const bit_pointer& bit_pointer::operator=(bool _value)
{
	set_bit(_value);
	return *this;
}

bit_pointer::operator bool() const
{
	return get_bit();
}

bit_pointer& bit_pointer::operator++()
{
	if (bit_pos_ == bit_store_size_ - 1)
	{
		bit_pos_ = 0;
		++byte_pointer_;
	}
	else
	{
		bit_pos_++;
	}

	return *this;

}
bool bit_pointer::operator!=(const bit_pointer& _that)
{
	return bit_pos_ != _that.bit_pos_ || byte_pointer_ != _that.byte_pointer_;
}

bool bit_pointer::operator*()
{
	return get_bit();
}