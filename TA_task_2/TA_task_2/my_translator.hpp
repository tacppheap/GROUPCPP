#pragma once

arg_pcd_t my_translator::StringArgTr(string _string)
{

	arg_pcd_t temp = 0;
	size_t ssize = _string.size();
	for (int i = 0; i < ssize; i++)
	{
		if (_string[ssize - i - 1]< '0' || _string[ssize - i - 1]> '9')
		{
			return -1;
		}
		temp += pow(10, i) * (_string[ssize - i - 1] - '0');
	}
	return temp;
}


ERROR_CODE my_translator::translate(string _ipath, string _opath)
{
	std::ifstream fin;
	fin.open(_ipath);
	std::ofstream fout(_opath, std::ios_base::binary);
	size_t tr_line = 0;

	if (!fin.is_open())
	{
		return ERROR(FILE_NOT_FOUND, tr_line);
	}

	string stemp;
	string cmd_name;
	string arg;
	cmd_pcd_t cmd_proc_code;
	arg_pcd_t reg_proc_code;

	while (std::getline(fin, stemp))
	{
		++tr_line;
		cmd_name = "";
		int char_pos = 0;

		while (stemp[char_pos])
		{
			if (stemp[char_pos] == ' ')
			{
				break;
			}
			cmd_name.push_back(stemp[char_pos++]);
		}

		arg = "";

		while (stemp[char_pos])
		{
			if (stemp[char_pos] == ' ')
			{
				char_pos++;
			}
			else
			{
				while (stemp[char_pos])
				{
					if (stemp[char_pos] == ' ')
					{
						break;
					}
					arg.push_back(stemp[char_pos++]);
				}

				break;
			}
		}

		cmd_proc_code = 0;
		reg_proc_code = 0;

		if (arg == "")
		{
			cmd_proc_code = dictionary::find_cmd_tr(cmd_name, EMPTY);

			if (!cmd_proc_code)
			{
				return ERROR(CMD_NOT_FOUND, tr_line);
			}

			fout.write(&cmd_proc_code, dictionary::cmd_size_);
			continue;
		}

		reg_proc_code = dictionary::find_reg_tr(arg);

		if (!reg_proc_code)
		{
			cmd_proc_code = dictionary::find_cmd_tr(cmd_name, CONST);

			if (!cmd_proc_code)
			{
				return ERROR(CMD_NOT_FOUND, tr_line);
			}

			fout.write(&cmd_proc_code, dictionary::cmd_size_);

			arg_pcd_t temp_arg = StringArgTr(arg);

			if (temp_arg < 0)
			{
				return ERROR(NOT_VALID_ARG, tr_line);
			}

			fout.write((char*)&temp_arg, dictionary::arg_size_);
			continue;
		}

		cmd_proc_code = dictionary::find_cmd_tr(cmd_name, REG);

		if (!cmd_proc_code)
		{
			return ERROR(CMD_NOT_FOUND, tr_line);
		}

		fout.write(&cmd_proc_code, dictionary::cmd_size_);
		fout.write((char*)&reg_proc_code, dictionary::arg_size_);
	}

	return NO_TR_ERROR;
}


