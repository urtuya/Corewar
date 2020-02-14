#include "head.h"

void	get_oper_code(t_cursor *cursor, unsigned char *arena)
{
	if (cursor->cycles_before_op == 0)
	{
		cursor->op_code = arena[ft_addr(cursor->cur_position)] - 1;
		if (cursor->op_code >= 0 && cursor->op_code <= 0xF)
			cursor->cycles_before_op = op_tab[cursor->op_code].cycles_to_exec;
		else
			cursor->cycles_before_op = 0;
	}
}

void	decrease_cycle_before_op(t_cursor *cursor)
{
	if ((cursor->cycles_before_op) > 0)
		(cursor->cycles_before_op)--;
}

void	set_types_as_needed(int *arg_type, int num)
{	
	int i;

	i = 0;
	while (i < num)
	{
		if (arg_type[i] == IND_CODE)
			arg_type[i] = T_IND;
		else if (arg_type[i] != IND_CODE && arg_type[i] != DIR_CODE
				&& arg_type[i] != REG_CODE)
			return ;
		i++;
	}
}

int		try_exec_oper(t_cursor *cursor, unsigned char *arena) // 	NEED CHECK FOR EVERY OPERATION
{
	if (!(cursor->op_code >= 0 && cursor->op_code <= 0xF))
	{
		cursor->cur_position = ft_addr(cursor->cur_position + 1);
		return (0);
	}
	// THIS if-esle FOR GETIING cursor->arg ONLY
	if (op_tab[cursor->op_code].code_type_args) // 1 = exist, 0 - non
	{
		cursor->arg_type[0] = (arena[ft_addr(cursor->cur_position + 1)] & 0b11000000) >> 6; // EBUCHAYA MASKA
		cursor->arg_type[1] = (arena[ft_addr(cursor->cur_position + 1)] & 0b00110000) >> 4; // now MUST work
		cursor->arg_type[2] = (arena[ft_addr(cursor->cur_position + 1)] & 0b00001100) >> 2; // kill yourself if not
		set_types_as_needed(cursor->arg_type, op_tab[cursor->op_code].arg_num);
	}
	else
		cursor->arg_type[0] = op_tab[cursor->op_code].arg[0]; //  -- T_REG or T_DIR
	// THIS FOR CHECKING TYPES OF ARGUMENTS FROM op_tab and for register numbers
	if (!check_arg_type(cursor) || !check_registers(cursor, arena)) // checking for every operation IM GENIUS
		return (0);
	return (1);
}

void	in_cycle(t_vm *vm) //25 lines)))))))
{
	t_cursor *cursor;

	cursor = vm->cursor;
	while (cursor)
	{
		(vm->num_of_cycles)++;
		(vm->cycles_before_check)--;
		while (cursor)
		{   //----------IN CYCLE
			get_oper_code(cursor, vm->arena);
			decrease_cycle_before_op(cursor);
			if (cursor->cycles_before_op == 0)
			{
				if (try_exec_oper(cursor, vm->arena))					// get ready before exec_oper
					vm->do_oper[cursor->op_code](cursor, vm);		 // do_oper is operation №op_code from operations.c YOU NEED FULL VM FOR LIVE AND OTHER OPERS, NOT JUST ARENA
				cursor->cur_position = ft_addr(cursor->cur_position + cursor->bytes_to_next_op);
				cursor->bytes_to_next_op = 0;
			}
			cursor = cursor->next;
		}
		if ((vm->cycles_to_die > 0 && vm->cycles_before_check == 0)
			|| vm->cycles_to_die <= 0)
			inspection(vm, vm->cursor);
		cursor = vm->cursor;
	}
}
