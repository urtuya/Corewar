#include "head.h"

void	get_oper_code(t_cursor *cursor, unsigned char *arena)
{
	if (cursor->cycles_before_op == 0)
	{
		// ft_printf("id = %d  cur_position = %d\n",cursor->id, cursor->cur_position);
		cursor->op_code = arena[ft_addr(cursor->cur_position)] - 1;
		if (cursor->op_code >= 0 && cursor->op_code <= 0xF)
		{
			// printf("getopcode CYCLENUMBER );
			// ft_printf("OP_cODE: %d\n", cursor->op_code);
			cursor->cycles_before_op = op_tab[cursor->op_code].cycles_to_exec;
			// printf("cycles to exec = %d\n", cursor->cycles_before_op);
		}
		else
		{
			cursor->cycles_before_op = 0;
			// ft_printf("OPCODE IS BAD count: %d\n", count);
			// printf("OPCODE IS %d\n", cursor->op_code);
		}
	}
}

void	decrease_cycle_before_op(t_cursor *cursor)
{
	if ((cursor->cycles_before_op) > 0)
		(cursor->cycles_before_op)--;
}

int		try_exec_oper(t_cursor *cursor, unsigned char *arena) // 	NEED CHECK FOR EVERY OPERATION
{
	if (!(cursor->op_code >= 0 && cursor->op_code <= 0xF))
	{
		// ft_printf("BAD OPCODE: pos + 1\n");
		cursor->cur_position = ft_addr(cursor->cur_position + 1);
		return (0);
	}
	// THIS if-esle FOR GETIING cursor->arg ONLY
	if (op_tab[cursor->op_code].code_type_args) // 1 = exist, 0 - non
	{
		// ft_printf("ARG CODE: %08b(bin) %d(dec)\n", arena[cursor->cur_position + 1], arena[cursor->cur_position + 1]);
		cursor->arg_type[0] = (arena[ft_addr(cursor->cur_position + 1)] & 0b11000000) >> 6; // EBUCHAYA MASKA
		cursor->arg_type[1] = (arena[ft_addr(cursor->cur_position + 1)] & 0b00110000) >> 4; // now MUST work
		cursor->arg_type[2] = (arena[ft_addr(cursor->cur_position + 1)] & 0b00001100) >> 2; // kill yourself if not
	}
	else
	{
		cursor->arg_type[0] = op_tab[cursor->op_code].arg[0]; //  -- T_REG or T_DIR
	}
	
	// THIS FOR CHECKING TYPES OF ARGUMENTS FROM op_tab and for register numbers
	if (!check_arg_type(cursor) || !check_registers(cursor, arena)) // checking for every operation IM GENIUS
	{
		// ft_printf("NOT GUT ARG TYPES\n");
		return (0);
	}
	return (1);
}

void	start(t_vm *vm)
{
	t_cursor *cursor;
	static int count = 0;
	vm->cursor = init_first_cursors(vm);

	// print_list_of_cursors(vm->cursor);
	// printf("NUM OF CURSORS: %d\n", vm->num_of_cursors);

	cursor = vm->cursor;
	while (cursor)
	{
		(vm->num_of_cycles)++;
		(vm->cycles_before_check)--;
		while (cursor)
		{   //----------IN CYCLE
			// printf("CYCLENUMBBER %d\n", vm->num_of_cycles);
			get_oper_code(cursor, vm->arena);
			decrease_cycle_before_op(cursor);
			if (cursor->cycles_before_op == 0)
			{
				if (try_exec_oper(cursor, vm->arena))					// get ready before exec_oper
				{
					count++;
					vm->do_oper[cursor->op_code](cursor, vm);		 // do_oper is operation №op_code from operations.c YOU NEED FULL VM FOR LIVE AND OTHER OPERS, NOT JUST ARENA
					// if (count == 3)
					// 	exit(0);
				}
				// printf("bytes to next_ope = %d\n", cursor->bytes_to_next_op);
				cursor->cur_position = ft_addr(cursor->cur_position + cursor->bytes_to_next_op);
				cursor->bytes_to_next_op = 0;
				// printf("CUR_POS: %d\n", cursor->cur_position);
			}
			cursor = cursor->next;
		}
		// printf("CYCLES BEFORE CHECK: %d\n", vm->cycles_before_check);
		// CHECKS AFTER CYCLES_TO_DIE
		// if (vm->num_of_cycles == 3051)
		// {
		// 	printf("cycles before check = %d\n", vm->cycles_before_check);
		// 	exit(0);
		// }
		if ((vm->cycles_to_die > 0 && vm->cycles_before_check == 0) //vm->cycles_to_die)
			|| vm->cycles_to_die <= 0)
			inspection(vm, vm->cursor);
		cursor = vm->cursor;
		// ft_printf("num of cycles: %d\n", vm->num_of_cycles);
	}
}
