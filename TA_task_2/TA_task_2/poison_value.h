#pragma once
namespace TA
{
	template<typename T>class poison
	{
	public :
		static const T value_ = T();
	};

	template<>
	class poison<int>
	{
	public:
		static const int value_ = -858993460;
	};

	template<>
	class poison<unsigned int>
	{
	public:
		static const unsigned int value_ = 8631004u;
	};

}
