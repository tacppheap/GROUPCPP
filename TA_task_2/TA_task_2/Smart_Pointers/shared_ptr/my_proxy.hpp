#pragma once

using TA::proxy;

template<typename T>
std::list<proxy_store_element> proxy<T>::store_ = std::list<proxy_store_element>();

template<typename T>
proxy<T>::proxy(pointer _resource) : resource_(_resource), number_of_clients_(1)
{
	Add(_resource, this);
	Arg1Dump(proxy, _resource);
}

template<typename T>
void proxy<T>::operator++()
{
	++number_of_clients_;
	Arg0Dump(operator++);
}

template<typename T>
void proxy<T>::operator--()
{
	--number_of_clients_;
	Arg0Dump(operator--);
	if (number_of_clients_ == 0)
	{
		Erase(this);
		delete this;
	}
}


template<typename T>
typename proxy<T>::reference proxy<T>::get_resource_ref()
{
	return *resource_;
}

template<typename T>
typename proxy<T>::pointer proxy<T>::get_resource_ptr()
{
	return resource_;
}

template<typename T>
size_t proxy<T>::get_number_of_clients()
{
	return number_of_clients_;
}


template<typename T>
void proxy<T>::dump()
{
	std::cout << "number_of_clients_ = " << number_of_clients_ << "\n" << "resource_ = " << resource_ << "\n";
	store_dump();

}

template<typename T>
proxy<T>::~proxy()
{
	Arg0Dump(~proxy);
	delete resource_;
}

template<typename T>
void proxy<T>::store_dump()
{
	std::cout << "store_ :" << "\n";
	for (std::list<proxy_store_element>::iterator it = store_.begin(); it != store_.end(); it++)
	{
		std::cout << "            " << (*it).resource_ << "----------------" << (*it).proxy_ << "\n";
	}
}

template<typename T>
void proxy<T>::Add(void* _resource, void* _proxy)
{
	store_.push_back(proxy_store_element(_resource, _proxy));
	printf("\nAdd(%X, %X)\n", _resource, _proxy);
	store_dump();

}

template<typename T>
void* proxy<T>::FindProxy(void* _resource)
{
	for (std::list<proxy_store_element>::iterator it = store_.begin(); it != store_.end(); it++)
	{
		if ((*it).resource_ == _resource)
			return (*it).proxy_;
	}
	return nullptr;
}

template<typename T>
void proxy<T>::Erase(void* _proxy)
{
	for (std::list<proxy_store_element>::iterator it = store_.begin(); it != store_.end(); it++)
	{
		if ((*it).proxy_ == _proxy)
		{
			store_.erase(it);
			printf("\nErase(%X)\n", _proxy);
			store_dump();
			return;
		}
	}
}

