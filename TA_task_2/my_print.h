#pragma once


namespace TA
{
	void print(const char* string)
	{
		return;
	}

	template <typename T, typename... Args>
	void print(const char* str, T val, Args... args)
	{
		while (str)
		{
			if (*str != '#')
				std::cout << *(str++);
			else
			{
				std::cout << val;
				print(str + 1, args...);
				break;
			}
		}
	}
}