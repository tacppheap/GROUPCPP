#pragma once

my_processor::my_processor()
{
	reg_store_.fill(0);
}

int my_processor::FindLable(arg_pcd_t _lable_num)
{
	for (int i = 0; i < lable_store_.size(); i++)
	{
		if (lable_store_[i].lable_num_ == _lable_num)
		{
			return lable_store_[i].next_cmd_num_;
		}

	}
	return -1;
}

void my_processor::RecognizeWhatTODO(string _path)
{
	std::ifstream fin;
	fin.open(_path, std::ios_base::binary);
	TODO_list_.clear();
	if (!fin.is_open())
	{
		return;
	}

	cmd_pcd_t cmd_proc_code;
	arg_pcd_t arg_proc_code;

	while (fin.read(&cmd_proc_code, dictionary::cmd_size_))
	{
		const cmd* cmd_ptr = dictionary::find_cmd(cmd_proc_code);
		if (!cmd_ptr)
		{
			return;
		}

		if (cmd_ptr->arg_type_ == EMPTY)
		{
			TODO_list_.push_back(cmd_TODO(cmd_ptr));
		}
		else
		{
			fin.read((char*)&arg_proc_code, dictionary::arg_size_);
			if (cmd_ptr->cmd_type_ == LABLE_CMD)
			{
				lable_store_.push_back(lable(arg_proc_code, TODO_list_.size()));
				continue;
			}
			TODO_list_.push_back(cmd_TODO(cmd_ptr, arg_proc_code));
		}

	}
}

EXECUTE_ERROR my_processor::Execute()
{
	size_t exe_cmd_num = 0;

	while (!reg_store_[EOP_REG] && exe_cmd_num < TODO_list_.size())
	{
		cmd_TODO temp_cmd = TODO_list_[exe_cmd_num++];

		switch (temp_cmd.cmd_->cmd_type_)
		{
		case PUSH_CMD:
		{
			stack_.push(reg_store_[dictionary::find_reg(temp_cmd.arg_proc_code_)]);
			break;
		}
		case PUSH_CONST_CMD:
		{
			stack_.push(temp_cmd.arg_proc_code_);
			break;
		}
		case DIV_CMD:
		{
			reg_store_[X5_REG] = stack_.pop();
			reg_store_[X4_REG] = stack_.pop();
			reg_store_[DIV_REG] = reg_store_[X4_REG] / reg_store_[X5_REG];
			reg_store_[MOD_REG] = reg_store_[X4_REG] % reg_store_[X5_REG];
			break;
		}
		case ADD_CMD:
		{
			stack_.push(stack_.pop() + stack_.pop());
			break;
		}
		case JUMP_CMD:
		{
			size_t new_cmd_num = FindLable(temp_cmd.arg_proc_code_);
			if (new_cmd_num >= 0)
			{
				exe_cmd_num = new_cmd_num;
			}
			break;
		}

		case JNE_CMD:
		{
			if (stack_.pop() != stack_.pop())
			{
				size_t new_cmd_num = FindLable(temp_cmd.arg_proc_code_);
				if (new_cmd_num >= 0)
				{
					exe_cmd_num = new_cmd_num;
				}
			}
			break;
		}
		case JAE_CMD:
		{
			if (stack_.pop() >= stack_.pop())
			{
				size_t new_cmd_num = FindLable(temp_cmd.arg_proc_code_);
				if (new_cmd_num >= 0)
				{
					exe_cmd_num = new_cmd_num;
				}
			}
			break;
		}

		case JBE_CMD:
		{
			if (stack_.pop() <= stack_.pop())
			{
				size_t new_cmd_num = FindLable(temp_cmd.arg_proc_code_);
				if (new_cmd_num >= 0)
				{
					exe_cmd_num = new_cmd_num;
				}
			}
			break;
		}

		case JE_CMD:
		{
			if (stack_.pop() == stack_.pop())
			{
				size_t new_cmd_num = FindLable(temp_cmd.arg_proc_code_);
				if (new_cmd_num >= 0)
				{
					exe_cmd_num = new_cmd_num;
				}
			}
			break;
		}

		case JA_CMD:
		{
			if (stack_.pop() > stack_.pop())
			{
				size_t new_cmd_num = FindLable(temp_cmd.arg_proc_code_);
				if (new_cmd_num >= 0)
				{
					exe_cmd_num = new_cmd_num;
				}
			}
			break;
		}

		case JB_CMD:
		{
			if (stack_.pop() < stack_.pop())
			{
				size_t new_cmd_num = FindLable(temp_cmd.arg_proc_code_);
				if (new_cmd_num >= 0)
				{
					exe_cmd_num = new_cmd_num;
				}
			}
			break;
		}

		case POP_CMD:
		{
			reg_store_[dictionary::find_reg(temp_cmd.arg_proc_code_)] = stack_.pop();
			break;
		}

		case CALL_CMD:
		{

			size_t new_cmd_num = FindLable(temp_cmd.arg_proc_code_);
			if (new_cmd_num >= 0)
			{
				if (ret_addr_stack_.push(exe_cmd_num) == STACK_IS_FULL)
					break;
				exe_cmd_num = new_cmd_num;

			}
			break;
		}

		case RET_CMD:
		{
			exe_cmd_num = ret_addr_stack_.pop();
			break;
		}

		case SUB_CMD:
		{
			stack_.push(stack_.pop() - stack_.pop());
			break;
		}

		case EOP_CMD:
		{
			reg_store_[EOP_REG] = 1;
			break;
		}

		case MULT_CMD:
		{
			stack_.push(stack_.pop() * stack_.pop());
			break;
		}

		};
	}
	return NO_EXE_ERROR;
}
