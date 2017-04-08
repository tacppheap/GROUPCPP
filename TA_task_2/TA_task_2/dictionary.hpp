#pragma once
cmd_pcd_t dictionary::find_cmd_tr(string _cmd_name, arg_type _arg_type)
{
	for (int cmd_num = 0; cmd_num < cmd_list_.capacity(); cmd_num++)
	{
		if (cmd_list_[cmd_num].name_ == _cmd_name && cmd_list_[cmd_num].arg_type_ == _arg_type)
		{
			return cmd_list_[cmd_num].proc_code_;
		}
	}
	return 0b00000000;
}

arg_pcd_t dictionary::find_reg_tr(string _reg_name)
{
	for (int reg_num = 0; reg_num < reg_list_.capacity(); reg_num++)
	{
		if (reg_list_[reg_num].name_ == _reg_name)
		{
			return reg_list_[reg_num].proc_code_;
		}
	}
	return 0;
}

const cmd* dictionary::find_cmd(cmd_pcd_t _proc_code)
{
	for (int cmd_num = 0; cmd_num < cmd_list_.capacity(); cmd_num++)
	{
		if (cmd_list_[cmd_num].proc_code_ == _proc_code)
		{
			return &cmd_list_[cmd_num];
		}
	}
	return NULL;
}

reg_type dictionary::find_reg(arg_pcd_t _proc_code)
{
	for (int reg_num = 0; reg_num < reg_list_.capacity(); reg_num++)
	{
		if (reg_list_[reg_num].proc_code_ == _proc_code)
		{
			return reg_list_[reg_num].reg_type_;
		}
	}
	return UNKNOWN_REG;
}