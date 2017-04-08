#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "dictionary.h"
#include <math.h>

using std::string;

enum  ERROR_CODE
{
	NO_TR_ERROR,
	FILE_NOT_FOUND,
	CMD_NOT_FOUND,
	NOT_VALID_ARG
};

inline ERROR_CODE ERROR(ERROR_CODE _error, size_t _line)
{
	printf("\nError in line: %i\n", _line);
	return _error;
}

static class my_translator
{
private:
	//-------------------------------------------------------------------------
	//! Convert argument from array of chars to arg_pcd_t
	//-------------------------------------------------------------------------
	static arg_pcd_t StringArgTr(string _string);
public:
	static ERROR_CODE translate(string _ipath, string _opath);
};


#include "my_translator.hpp"
