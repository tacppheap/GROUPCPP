#pragma once
#include "Assembler/dictionary.h"
#include "Stack/Stack.h"
#include <string>
#include <fstream>
#include <iostream>

enum EXECUTE_ERROR
{
	NO_EXE_ERROR
};


class cmd_TODO
{
private:

public:
	const cmd*	cmd_;
	arg_pcd_t	arg_proc_code_;

	cmd_TODO(const cmd* _cmd, arg_pcd_t _arg_proc_code = 0) : 
		cmd_(_cmd), 
		arg_proc_code_(_arg_proc_code){}
};

class lable
{
public:
	arg_pcd_t lable_num_;
	size_t next_cmd_num_;

	lable (arg_pcd_t _lable_num,	size_t _next_cmd_num) : 
		lable_num_(_lable_num),
		next_cmd_num_(_next_cmd_num){}
};

class my_processor
{
private:
	int FindLable(arg_pcd_t _lable_num);
	
public:
	static const size_t stack_len_ = 15;
	static const size_t ret_addr_stack__len_ = 15;
	static const size_t reg_store_len_ = 15;

	Stack<arg_pcd_t, stack_len_> stack_;
	vector<cmd_TODO> TODO_list_;
	Array<arg_pcd_t, reg_store_len_> reg_store_;
	vector<lable> lable_store_;
	Stack<arg_pcd_t, stack_len_> ret_addr_stack_;	

	my_processor();
	my_processor(const my_processor& _that) = delete;
	//-----------------------------------------------------------------------------
	//! Open the source binary file and recognize cmds and arguments. Fill TODO_list;
	//-----------------------------------------------------------------------------
	void RecognizeWhatTODO(string _path);
	EXECUTE_ERROR Execute();
};

#include "my_processor.hpp"


 