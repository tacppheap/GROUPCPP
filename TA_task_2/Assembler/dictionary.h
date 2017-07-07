#pragma once
#include <string>
#include  <vector>
#include <map>
using std::vector;
using std::string;
using std::pair;


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
	reg_type reg_type_;

	reg(reg_type _reg_type) :
		reg_type_ (   _reg_type   )	{}


};

class cmd
{
public:
	cmd_type cmd_type_;
	arg_type arg_type_;

	cmd(cmd_type _cmd_type, arg_type _arg_type) :
		cmd_type_ (	_cmd_type	),
		arg_type_ (	_arg_type	){}
};

static class dictionary
{
public:
	static const std::map<pair<string, arg_type>, cmd_pcd_t> cmd_list_tr;
	static const std::map<cmd_pcd_t, cmd> cmd_list_proc;
	static const std::map<string, arg_pcd_t> reg_list_tr;
	static const std::map<arg_pcd_t, reg_type> reg_list_proc;

	static const size_t cmd_size_;
	static const size_t arg_size_ ;

	static cmd_pcd_t find_cmd_tr(string _cmd_name, arg_type _arg_type);
	static arg_pcd_t find_reg_tr(string _reg_name);
	static const cmd* find_cmd(cmd_pcd_t _proc_code);
	static reg_type find_reg(arg_pcd_t _proc_code);
};




const size_t			dictionary::cmd_size_        = sizeof(cmd_pcd_t);
const size_t			dictionary::arg_size_		 = sizeof(arg_pcd_t);

typedef pair<string, arg_type> key;

const std::map<cmd_pcd_t, cmd> dictionary::cmd_list_proc =
{
	{ 0b00000001,  cmd(PUSH_CMD, REG) },
	{ 0b00000010, cmd(PUSH_CONST_CMD, CONST) },
	{ 0b00000011, cmd(ADD_CMD, EMPTY) },
	{ 0b00000100, cmd(DIV_CMD, EMPTY) },
	{ 0b00000101, cmd(EOP_CMD, EMPTY) },
	{ 0b00000110, cmd(POP_CMD, REG) },
	{ 0b00000111, cmd(LABLE_CMD, CONST) },
	{ 0b00001000, cmd(JUMP_CMD, CONST) },
	{ 0b00001001, cmd(JNE_CMD, CONST) },
	{ 0b00001010, cmd(JE_CMD, CONST) },
	{ 0b00001011, cmd(JA_CMD, CONST) },
	{ 0b00001100, cmd(JAE_CMD, CONST) },
	{ 0b00001101, cmd(JB_CMD, CONST) },
	{ 0b00001110, cmd(JBE_CMD, CONST) },
	{ 0b00001111, cmd(CALL_CMD, CONST) },
	{ 0b00010000, cmd(RET_CMD, EMPTY) },
	{ 0b00010001, cmd(MULT_CMD, EMPTY) },
	{ 0b00010010, cmd(SUB_CMD, EMPTY) },

};

const std::map<pair<string, arg_type>, cmd_pcd_t> dictionary::cmd_list_tr =
{
	{ key("PUSH",		REG),	0b00000001 },
	{ key("PUSH",		CONST), 0b00000010 },
	{ key("ADD",		EMPTY), 0b00000011 },
	{ key("DIV",		EMPTY), 0b00000100 },
	{ key("EOP",		EMPTY), 0b00000101 },
	{ key("POP",		REG),	0b00000110 },
	{ key("LABLE",		CONST), 0b00000111 },
	{ key("JUMP",		CONST), 0b00001000 },
	{ key("JNE",		CONST), 0b00001001 },
	{ key("JE",			CONST), 0b00001010 },
	{ key("JA",			CONST), 0b00001011 },
	{ key("JAE",		CONST), 0b00001100 },
	{ key("JB",			CONST), 0b00001101 },
	{ key("JBE",		CONST), 0b00001110 },
	{ key("CALL",		CONST), 0b00001111 },
	{ key("RET",		EMPTY), 0b00010000 },
	{ key("MULT",		EMPTY), 0b00010001 },
	{ key("SUB",		EMPTY), 0b00010010 }

};


const std::map<arg_pcd_t, reg_type> dictionary::reg_list_proc =
{
	{ 1,		X1_REG },
	{ 2,	    X2_REG },
	{ 3,		X3_REG},
	{ 11,		DIV_REG },
	{ 10,		MOD_REG }
};

const std::map<string, arg_pcd_t> dictionary::reg_list_tr = 
{
	{ "X1",		1 },
	{ "X2",		2 },
	{ "X3",		3 },
	{ "DIV_REG",11 },
	{ "MOD_REG",10 }
};


#include "dictionary.hpp"







