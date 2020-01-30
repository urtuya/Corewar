#include "head.h"

int		arg_num(int op_code)
{
	if (op_code == LIVE || op_code == ZJMP || op_code == FORK ||
			op_code == LFORK || op_code == AFF)
		return (1);
	else if (op_code == LD || op_code == ST || op_code == LLD)
		return (2);
	else if (op_code >= 0x04 && op_code <= 0x08 &&
			(op_code == LDI || op_code == STI || op_code == LLDI))
		return (3);
	else
		error("%s", "NO SUCH OP_CODE");
	return (0);
}

int		one_arg(int op_code, int arg_num)
{
	if (arg_num == 1 && (op_code == LIVE || op_code == ZJMP || op_code == FORK ||
			op_code == LFORK || op_code == AFF))
		return (1);
	else if (arg_num == 2 && (op_code == LD || op_code == ST || op_code == LLD))
		return (1);
	else if (arg_num == 3 && op_code >= 0x04 && op_code <= 0x08 &&
			(op_code == LDI || op_code == STI || op_code == LLDI))
		return (1);
	return (0);
}

int		single_arg_code(int op_code)
{
	if (op_code == LIVE || op_code == FORK || op_code == LFORK)
		return (T_DIR);
	else
		return (T_REG);
}

int		size_of_arg(int arg_code, int size_of_t_dir) // return size of arguments in bytes
{
	if (IS_REG(arg_code))
		return (1);
	else if (IS_IND(arg_code) || (IS_DIR(arg_code) && size_of_t_dir))
		return (2);
	else if (IS_DIR(arg_code) && !size_of_t_dir)
		return (4);
	else
	{
		error("%s\n", "arg_size");  
		return (0);				//	BECAUSE OF WARNING
	}
}

