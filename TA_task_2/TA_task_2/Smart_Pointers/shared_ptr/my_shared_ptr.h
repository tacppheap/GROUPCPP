#pragma once
#include "my_proxy.h"
#include "debug_tools.h"
#include "my_exceptions.h"
namespace TA
{
	template<typename T> class shared_ptr
	{
	public:
		typedef T& reference;
		typedef T* pointer;

		explicit shared_ptr(pointer&& _pointer);
		shared_ptr(const shared_ptr<T>& _that);
		~shared_ptr();
		const shared_ptr<T>& operator=(const shared_ptr<T>& _that);
		reference operator*();
		operator pointer();
		pointer operator->();
	private:
		proxy<T>* proxy_;
		void dump();
	};

}
#include "my_shared_ptr.hpp"
