#pragma once
#include <cstring>
#include <cstdlib>

inline void* operator new[](size_t _size, int _init)
{
	void* _pointer = malloc(_size);
	memset(_pointer, _init, _size);
	return _pointer;
}

