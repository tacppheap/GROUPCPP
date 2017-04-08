#pragma once
#include <string>
#include  <vector>
using std::vector;
using std::string;


enum cmd_type
{
	PUSH_CMD,
	PUSH_CONST_CMD,
	POP_CMD,
	ADD_CMD,
	DIV_CMD,
	EOP_CMD,
	LABLE_CMD,
	JUMP_CMD,
	JNE_CMD,
	JE_CMD,
	JA_CMD,
	JAE_CMD,
	JB_CMD,
	JBE_CMD,
	CALL_CMD,
	RET_CMD,
	MULT_CMD,
	SUB_CMD
};

enum reg_type
{
	DIV_REG = 10,
	MOD_REG,
	EOP_REG = 14,
	X1_REG  =  0,
	X2_REG,
	X3_REG,
	X4_REG,
	X5_REG,
	UNKNOWN_REG
};

enum arg_type
{
	EMPTY,
	REG,
	CONST
};

//-----------------------------------------------------------------------------
//! Variables of those types are storeges of bytes for binary representation of cmds and arguments
//-----------------------------------------------------------------------------
typedef int arg_pcd_t;
typedef char cmd_pcd_t;


class reg
{
public:
	string name_;
	reg_type reg_type_;
	arg_pcd_t proc_code_;

	reg(string _name, reg_type _reg_type , arg_pcd_t _proc_code) :
		reg_type_ (   _reg_type   ),
		name_     (	  _name       ),
		proc_code_(	  _proc_code  ) {}
};

class cmd
{
public:

	string name_;
	cmd_type cmd_type_;
	cmd_pcd_t proc_code_;
	arg_type arg_type_;

	cmd(string _name, cmd_type _cmd_type, cmd_pcd_t _proc_code, arg_type _arg_type) :
		name_     (	_name		),
		cmd_type_ (	_cmd_type	),
		proc_code_(	_proc_code	),
		arg_type_ (	_arg_type	){}
};

static class dictionary
{
public:
	static const vector<cmd> cmd_list_;
	static const vector<reg> reg_list_;

	static const size_t cmd_size_;
	static const size_t arg_size_ ;

	static cmd_pcd_t find_cmd_tr(string _cmd_name, arg_type _arg_type);
	static arg_pcd_t find_reg_tr(string _reg_name);
	static const cmd* find_cmd(cmd_pcd_t _proc_code);
	static reg_type find_reg(arg_pcd_t _proc_code);
};




const size_t			dictionary::cmd_size_        = sizeof(cmd_pcd_t);
const size_t			dictionary::arg_size_		 = sizeof(arg_pcd_t);

const vector<cmd>		dictionary::cmd_list_ = vector<cmd>
{
	cmd("PUSH"	 ,		PUSH_CMD,			0b00000001,		REG  ),
	cmd("PUSH"	 ,		PUSH_CONST_CMD,		0b00000010,		CONST),
	cmd("ADD"	 ,		ADD_CMD,			0b00000011,		EMPTY),
	cmd("DIV"	 ,		DIV_CMD,			0b00000100,		EMPTY),
	cmd("EOP"	 ,		EOP_CMD,			0b00000101,		EMPTY),
	cmd("POP"	 ,		POP_CMD,			0b00000110,		REG),
	cmd("LABLE"	 ,		LABLE_CMD,			0b00000111,		CONST),
	cmd("JUMP"	 ,		JUMP_CMD,			0b00001000,		CONST),
	cmd("JNE"	 ,		JNE_CMD,			0b00001001,		CONST),
	cmd("JE"	 ,		JE_CMD,				0b00001010,		CONST),
	cmd("JA"	 ,		JA_CMD,				0b00001011,		CONST),
	cmd("JAE"	 ,		JAE_CMD,			0b00001100,		CONST),
	cmd("JB"	 ,		JB_CMD,				0b00001101,		CONST),
	cmd("JBE"	 ,		JBE_CMD,			0b00001110,		CONST),
	cmd("CALL"	 ,		CALL_CMD,			0b00001111,		CONST),
	cmd("RET"	 ,		RET_CMD,			0b00010000,		EMPTY),
	cmd("MULT"	 ,		MULT_CMD,			0b00010001,		EMPTY),
	cmd("SUB"	 ,		SUB_CMD,			0b00010010,		EMPTY)
};

const vector<reg>		dictionary::reg_list_ = vector<reg>
{
	reg("X1",		X1_REG,				1),
	reg("X2",		X2_REG,				2),
	reg("X3",		X3_REG,				3),
	reg("DIV_REG",	DIV_REG,			11),
	reg("MOD_REG",	MOD_REG,			10)

};

#include "dictionary.hpp"







