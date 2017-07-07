#pragma once
#include "my_exceptions.h"
#include "debug_tools.h"
namespace TA
{
	template <typename T> class	unique_ptr
	{
		typedef T& reference;
		typedef T* pointer;

	public:
		unique_ptr(pointer&& _pointer = nullptr);
		unique_ptr(unique_ptr<T>& _that) = delete;
		unique_ptr(unique_ptr<T>&& _that);
		~unique_ptr();
		const unique_ptr<T>& operator=(unique_ptr<T>& _that) = delete;
		const unique_ptr<T>& operator=(unique_ptr<T>&& _that);
		reference operator*();
		operator pointer() = delete;
		pointer operator->();
	private:
		pointer pointer_;
		void dump() const;

	};
}
#include "my_unique_ptr.hpp"