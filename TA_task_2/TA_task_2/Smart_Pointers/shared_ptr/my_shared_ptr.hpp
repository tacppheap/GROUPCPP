#pragma once
using TA::shared_ptr;


template<typename T>
shared_ptr<T>::shared_ptr(pointer&& _pointer)
{
	proxy_ = (proxy<T>*)proxy<T>::FindProxy(_pointer);

	if (proxy_ == nullptr)
	{
		proxy_ = new proxy<T>(_pointer);
		Arg1Dump(shared_ptr, _pointer);
		return;
	}
	proxy_->operator++();
	Arg1Dump(shared_ptr, _pointer);
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& _that)
{
	proxy_ = _that.proxy_;
	proxy_->operator++();
	Arg1Dump(shared_ptr[copy], _that);
}


template<typename T>
shared_ptr<T>::~shared_ptr()
{
	if (proxy_ != nullptr)
	{
		proxy_->operator--();
		proxy_ = nullptr;
	}
	Arg0Dump(~shared_ptr);
}

template<typename T>
const shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr<T>& _that)
{
	proxy_->operator--();
	proxy_ = _that.proxy_;
	proxy_->operator++();
	Arg1Dump(operator=, &_that)
	return *this;
}

template<typename T>
typename shared_ptr<T>::reference shared_ptr<T>::operator*()
{
	if (proxy_ == nullptr)
		throw TA::no_init(__FUNCSIG__);
	return proxy_->get_resource_ref();
}

template<typename T>
shared_ptr<T>::operator pointer()
{
	return proxy_->get_resource_ptr();
}


template<typename T>
typename shared_ptr<T>::pointer shared_ptr<T>::operator->()
{
	return proxy_->get_resource_ptr();
}

template<typename T>
void shared_ptr<T>::dump()
{
	std::cout << "proxy_ = " << proxy_ << "\n";
}



