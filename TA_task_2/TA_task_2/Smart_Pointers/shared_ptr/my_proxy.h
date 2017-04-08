#pragma once
#include "debug_tools.h"
#include "proxy_store_element.h"
#include <list>

namespace TA
{
	template<typename T> class proxy
	{
	public:
		typedef T* pointer;
		typedef T& reference;

		proxy(pointer _resource);
		~proxy();
		void operator++();
		void operator--();
		reference get_resource_ref();
		pointer get_resource_ptr();
		size_t get_number_of_clients();
		static void* FindProxy(void* _resource);

	private: 
		size_t number_of_clients_;
		pointer resource_;
		void dump();
		static void store_dump();
		//---------------------------------------------------------------
		//! Store of proxies and objects corresponding to them
		//---------------------------------------------------------------
		static std::list<proxy_store_element> store_;
		//---------------------------------------------------------------
		//! Functions to add and erase records from store 
		//---------------------------------------------------------------
		static void Add(void* _resource, void* _proxy);
		static void Erase(void* _proxy);

	};
}

#include "my_proxy.hpp"

