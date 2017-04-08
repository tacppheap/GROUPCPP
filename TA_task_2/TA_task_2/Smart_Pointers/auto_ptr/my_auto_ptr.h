#pragma once
#include "my_exceptions.h"
#include "debug_tools.h"
namespace TA
{
	template <typename T> class	auto_ptr
	{
		typedef T& reference;
		typedef T* pointer;

	public:
		auto_ptr(pointer&& _pointer = nullptr);
		auto_ptr(auto_ptr<T>& _that);
		auto_ptr(auto_ptr<T>&& _that);
		~auto_ptr();
		const auto_ptr<T>& operator=(auto_ptr<T>& _that);
		const auto_ptr<T>& operator=(auto_ptr<T>&& _that);
		reference operator*();
		operator pointer();
		pointer operator->();
	private:
		pointer pointer_;
		void dump() const;

	};
}
#include "my_auto_ptr.hpp"

