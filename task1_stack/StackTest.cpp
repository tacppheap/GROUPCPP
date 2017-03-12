//--------------------------------------------
//! @file StackTest.h
//! Implements a stack class tests
//!
//! @author Petrov Mikhail, 2017 
//--------------------------------------------

#include "stack.h"
#include <cstdlib>
//--------------------------------------------
//! Macro to test
//! @parap what is object which should be tested
//! @param case is purpose of test
//--------------------------------------------
#define TEST(what, case) cout<<#what<<" test  :  "<<#case<<"\n\n";
//--------------------------------------------
//! Macro to test to check the condition correctness
//! @parap condition is expression to check
//--------------------------------------------
#define ASSERT_EQ(condition)\
			if(condition)\
				cout << "		Test succeed: " << #condition <<"\n\n";\
			else\
				cout << "		Test FAILED: " << #condition <<"\n\n";


void main()
{
	TEST(stack, PushSingleNumber)
	{
		stack _stack;
		_stack.push(3);
		ASSERT_EQ(_stack.top() == 3);
		ASSERT_EQ(_stack.pop() == 3);
		ASSERT_EQ(_stack.empty());
	}

	TEST(stack, CannotPushMore)
	{
		stack _stack;
		for (int i = 0; i < _stack.capacity(); i++)
			_stack.push(3 + i);
		ASSERT_EQ(_stack.push(3) == false);
		ASSERT_EQ(_stack.size() == _stack.capacity());
	}

	TEST(stack, DeleteFromEmptyStack)
	{
		stack _stack;
		ASSERT_EQ(_stack.pop() == 666);
		ASSERT_EQ(_stack.size() == 0)
	}

	TEST(stack, DeleteFromNOTEmptyStack)
	{
		stack _stack;

		for (int i = 0; i < _stack.capacity(); i++)
			_stack.push(3 + i);
		ASSERT_EQ(_stack.pop() == 3 + _stack.capacity() - 1);
		ASSERT_EQ(_stack.size() == _stack.capacity() - 1);
		_stack.pop();
	}

	system("pause");


}