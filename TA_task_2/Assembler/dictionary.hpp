#pragma once
cmd_pcd_t dictionary::find_cmd_tr(string _cmd_name, arg_type _arg_type)
{

	std::map<key, cmd_pcd_t>::const_iterator it = cmd_list_tr.find(key(_cmd_name, _arg_type));
	if (it != cmd_list_tr.end())
	{
		return it->second;
	}
	return 0b00000000;
}

arg_pcd_t dictionary::find_reg_tr(string _reg_name)
{

	std::map<string, arg_pcd_t>::const_iterator it = reg_list_tr.find(_reg_name);
	if (it != reg_list_tr.end())
	{
		return it->second;
	}
	return 0;
}

const cmd* dictionary::find_cmd(cmd_pcd_t _proc_code)
{

	std::map<cmd_pcd_t, cmd>::const_iterator it = cmd_list_proc.find(_proc_code);
	if (it != cmd_list_proc.end())
	{
		return &it->second;
	}
	return NULL;
}

reg_type dictionary::find_reg(arg_pcd_t _proc_code)
{

	std::map<arg_pcd_t, reg_type>::const_iterator it = reg_list_proc.find(_proc_code);
	if (it != reg_list_proc.end())
	{
		return it->second;
	}
	return UNKNOWN_REG;
}