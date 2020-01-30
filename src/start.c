#include "head.h"

t_op op_tab[17];

void	get_oper_code(t_cursor *cursor, unsigned char *arena)
{
	if (cursor->cycles_before_op == 0)
	{
		cursor->op_code = arena[cursor->cur_position] - 1;
		if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
		{
			cursor->cycles_before_op = op_tab[cursor->op_code].cycles_to_exec;
		}
		else
			cursor->cycles_before_op = 0;
		printf("if OPER: %s\n", op_tab[cursor->op_code].name);
	}
	// printf("IN FUNC: get_oper_code()\n");
}

void	decrease_cycle_before_op(t_cursor *cursor)
{
	if (cursor->cycles_before_op > 0)
	{
		cursor->cycles_before_op--;
		// printf("cycles before op: %d\n", cursor->cycles_before_op);
	}
	// printf("IN_FUNC: decrease_cycle_before_op()\n");
}

void	exec_oper(t_cursor *cursor, unsigned char *arena, void (*do_oper)(t_cursor*, unsigned char*)) // 	NEED CHECK FOR EVERY OPERATION
{
	if (!(cursor->op_code >= 0x01 && cursor->op_code <= 0x10))
	{
		cursor->cur_position += 1;
		return ;
	}
	if (op_tab[cursor->op_code].code_type_args) // 1 = exist, 0 - non
	{
		ft_printf("ARG CODE: %08b\n", arena[cursor->cur_position + 1]);
		cursor->arg[0] = (arena[cursor->cur_position + 1] & 0b11000000) >> 6; // EBUCHAYA MASKA
		cursor->arg[1] = (arena[cursor->cur_position + 1] & 0b00110000) >> 4; // now MUST work
		cursor->arg[2] = (arena[cursor->cur_position + 1] & 0b00001100) >> 2; // kill yourself if not

		ft_printf("[1]: %02b\n", cursor->arg[0]);
		ft_printf("[2]: %02b\n", cursor->arg[1]);
		ft_printf("[3]: %02b\n", cursor->arg[2]);

	}
	else
	{
		cursor->arg[0] = op_tab[cursor->op_code].arg[0]; //  -- T_REG or T_DIR
		ft_printf("0 = %8b\n", cursor->arg[0]);
	}
	if (!check_arg_type(cursor) || !check_registers(cursor, arena)) // checking for every operation IM GENIUS
	{
		printf("NOT GUT ARG TYPES\n");
	}
	else
	{
		do_oper(cursor, arena);  // do oper
		// exit(0);
	}
	cursor->cur_position += cursor->bytes_to_next_op;
	printf("CURRENT POSITION: %zu\n", cursor->cur_position);
	printf("BYTECODE: %02x\n", arena[cursor->cur_position]);
	// else
	// 	// change cur_position
}

void	start(t_vm *vm)
{
	t_cursor *cursor;

	vm->cursor = init_first_cursors(vm);

	// print_list_of_cursors(vm->cursor);
	// printf("NUM OF CURSORS: %d\n", vm->num_of_cursors);

	cursor = vm->cursor;
	while (1)
	{
		while (cursor)
		{   //----------IN CYCLE
			
			ft_printf("%d:\n", cursor->id);
			get_oper_code(cursor, vm->arena);
			decrease_cycle_before_op(cursor);
			if (cursor->cycles_before_op == 0)
				exec_oper(cursor, vm->arena, vm->do_oper[cursor->op_code]);

			cursor = cursor->next;
		}
		cursor = vm->cursor;
		if ((vm->cycles_to_die > 0 && vm->num_of_cycles == vm->cycles_to_die)
			|| vm->cycles_to_die <= 0)
			inspection(vm, vm->cursor);
	}
}
