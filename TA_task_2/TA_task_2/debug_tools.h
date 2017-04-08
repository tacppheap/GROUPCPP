#pragma once
#include <iostream>

#define VALID_ASSERT(_pointer) \
		{\
			if (_pointer->IsValid())\
			{\
				_pointer->dump();\
				throw TA::invalid_object(__FUNCSIG__);\
			}\
		}

#define Arg0Dump(_name)\
			std::cout<<"\n"<<this<<":   "<<#_name<<"():\n";\
			dump();

#define Arg1Dump(_name, _arg1)\
			std::cout<<"\n"<<this<<":   "<<#_name<<"("<<_arg1<<"):\n";\
			dump();

#define Arg2Dump(_name, _arg1, _arg2)\
			std::cout<<"\n"<<this<<":   "<<#_name<<"("<<_arg1<<","<<_arg2<<"):\n";\
			dump();
