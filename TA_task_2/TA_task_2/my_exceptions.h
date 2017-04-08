#pragma once
#include <string>

namespace TA
{
	class my_exception
	{
		typedef std::string message_type;
	public:
		my_exception(std::string _message) : message_(_message) {}
		~my_exception() {}
		const message_type& get_message()
		{
			return message_;
		}
	private:
		const message_type  message_;
	};


	class out_of_range : public my_exception
	{
	public:
		out_of_range(std::string _message) : my_exception(_message) {}
	};


	class bad_alloc : public my_exception
	{
	public:
		bad_alloc(std::string _message) : my_exception(_message) {}
	};


	class no_init : public my_exception
	{
	public:
		no_init(std::string _message) : my_exception(_message) {}
	};


	class invalid_object : public my_exception
	{
	public:
		invalid_object(std::string _message) : my_exception(_message) {}
	};

}


