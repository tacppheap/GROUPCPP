#ifndef MY_EVENT_H
#define MY_EVENT_H

#include <vector>
#include <memory>

class EmptyArg
{

};

template <typename ClassType, typename ArgType> class function
{
public:
	typedef void(ClassType::*member_Function_signature_t)(ArgType _arg);

	function(member_Function_signature_t _Function) : Function_(_Function)
	{
	}

	void  operator()(std::shared_ptr<ClassType>& _obj, ArgType _arg)
	{
		((*(_obj.get())).*Function_)(_arg);
	}

private:

	member_Function_signature_t Function_;
};

template<typename ArgType> class Event
{
public:
	template<typename ClassType>
	void Add(std::shared_ptr<ClassType>& _obj, void(ClassType::*Function)(ArgType _arg))
	{
		store_.push_back(
			new holder<ClassType, function<ClassType, ArgType>>
			(
				_obj, function<ClassType, ArgType>(Function)
				)
		);
	}

	void invoke(ArgType _arg)
	{
		for (int i = 0; i < store_.size(); i++)
		{
			if (!store_[i]->invoke(_arg))
			{
				delete store_[i];
				store_[i--] = store_.back();
				store_.pop_back();

			}
		}
	}

	~Event()
	{
	}
private:

	class base_holder
	{
	public:
		virtual ~base_holder() = default;
		virtual bool invoke(ArgType& _arg) = 0;
	};

	template<typename ClassType, typename functionType>
	class holder : public base_holder
	{
	public:
		holder(std::shared_ptr<ClassType>& _obj, functionType _function) : obj_(_obj), function_(_function)
		{
		}

		bool invoke(ArgType& _arg) override
		{
			if (!obj_.expired())
			{
				function_(obj_.lock(), _arg);
				return true;
			}
			return false;
		}

		~holder() override
		{
		}

		functionType function_;
		std::weak_ptr<ClassType> obj_;
	};

	std::vector<base_holder*> store_;



};
#endif // MY_EVENT_H
