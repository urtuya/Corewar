#include "head.h"

void	get_oper_code(t_cursor *cursor, unsigned char *arena)
{
	static int count = 0;

	if (cursor->cycles_before_op == 0)
	{
		cursor->op_code = arena[cursor->cur_position] - 1;
		if (cursor->op_code >= 0 && cursor->op_code <= 0xF)
		{
			count = 0;
			ft_printf("OPER: %s\n", op_tab[cursor->op_code].name);
			cursor->cycles_before_op = op_tab[cursor->op_code].cycles_to_exec;
		}
		else
		{
			count++;
			cursor->cycles_before_op = 0;
			ft_printf("OPCODE IS BAD count: %d\n", count);
			printf("OPCODE IS %d\n", cursor->op_code);
		}
	}
}

void	decrease_cycle_before_op(t_cursor *cursor)
{
	if (cursor->cycles_before_op > 0)
		cursor->cycles_before_op--;
}

int		try_exec_oper(t_cursor *cursor, unsigned char *arena) // 	NEED CHECK FOR EVERY OPERATION
{
	if (!(cursor->op_code >= 0 && cursor->op_code <= 0xF))
	{
		ft_printf("BAD OPCODE: pos + 1\n");
		cursor->cur_position = (cursor->cur_position + 1) % MEM_SIZE;
		ft_printf("cur_pos = %d\n", cursor->cur_position);
		return (0);
	}
	// THIS if-esle FOR GETIING cursor->arg ONLY
	if (op_tab[cursor->op_code].code_type_args) // 1 = exist, 0 - non
	{
		ft_printf("ARG CODE: %08b(bin) %d(dec)\n", arena[cursor->cur_position + 1], arena[cursor->cur_position + 1]);
		cursor->arg_type[0] = (arena[cursor->cur_position + 1] & 0b11000000) >> 6; // EBUCHAYA MASKA
		cursor->arg_type[1] = (arena[cursor->cur_position + 1] & 0b00110000) >> 4; // now MUST work
		cursor->arg_type[2] = (arena[cursor->cur_position + 1] & 0b00001100) >> 2; // kill yourself if not

		ft_printf("[1]: %02b\n", cursor->arg_type[0]);
		ft_printf("[2]: %02b\n", cursor->arg_type[1]);
		ft_printf("[3]: %02b\n", cursor->arg_type[2]);

	}
	else
	{
		ft_printf("NO ARG CODE\n");
		cursor->arg_type[0] = op_tab[cursor->op_code].arg[0]; //  -- T_REG or T_DIR
		ft_printf("ARG = %2b\n", cursor->arg_type[0]);
	}
	
	// THIS FOR CHECKING TYPES OF ARGUMENTS FROM op_tab and for register numbers
	if (!check_arg_type(cursor) || !check_registers(cursor, arena)) // checking for every operation IM GENIUS
	{
		ft_printf("NOT GUT ARG TYPES\n");
		return (0);
	}
	return (1);
}

void	start(t_vm *vm)
{
	t_cursor *cursor;
	static int count = 0;
	// void (*do_oper)[16(t_cursor*, unsigned char*, int*);

	vm->cursor = init_first_cursors(vm);

	// print_list_of_cursors(vm->cursor);
	// printf("NUM OF CURSORS: %d\n", vm->num_of_cursors);

	cursor = vm->cursor;
	while (1)
	{
		vm->num_of_cycles++;
		while (cursor)
		{   //----------IN CYCLE
			// ft_printf("cursor ID: %d\n", cursor->id);
			get_oper_code(cursor, vm->arena);
			decrease_cycle_before_op(cursor);
			ft_printf("NUM OF CYCLES: %d\n", vm->num_of_cycles);
			ft_printf("CURRENT CURSOR CYCLES BEFORE OPERATION: %d\n", cursor->cycles_before_op);
			if (cursor->cycles_before_op == 0)
			{
				count++;
				if (try_exec_oper(cursor, vm->arena))					// get ready before exec_oper
				{
					vm->do_oper[cursor->op_code](cursor, vm/*vm->arena*/, &vm->num_of_cursors);		 // do_oper is operation №op_code from operations.c YOU NEED FULL VM FOR LIVE AND OTHER OPERS, NOT JUST ARENA
			
				}
				cursor->cur_position = (cursor->cur_position + cursor->bytes_to_next_op) % MEM_SIZE;

				if (count == 6)
					exit(0);
			}
			cursor = cursor->next;
		}
		// CHECKS AFTER CYCLES_TO_DIE
		if ((vm->cycles_to_die > 0 && vm->num_of_cycles == vm->cycles_to_die)
			|| vm->cycles_to_die <= 0)
			inspection(vm, vm->cursor);
		cursor = vm->cursor;
	}
}
