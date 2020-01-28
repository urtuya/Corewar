#include "head.h"

t_op op_tab[17];

int		ind(int op_code)
{
	if (!(op_code >= 0x01 && op_code <= 0x10))
	{
		ft_fprintf(stderr, "GET IND\n");
		exit (1);
	}
	return (op_code - 1);
}

void	try_to_exec(unsigned char *arena, t_cursor *cursor)
{

}

int		check_arguments(unsigned char *arena, t_cursor *cursor)
{
	// if (one_arg(cursor->op_code, 1) == 1)
	return (0);
}

void	get_oper_code(t_cursor *cursor, unsigned char *arena)
{
	if (cursor->cycles_before_op == 0)
	{
		cursor->op_code = arena[cursor->cur_position];
		if (cursor->op_code >= 0x01 && cursor->op_code <= 0x10)
		{
			cursor->cycles_before_op = op_tab[ind(cursor->op_code)].cycles_to_exec;
		}
		else
			cursor->cycles_before_op = 0;
	}
	printf("IN FUNC: get_oper_code()\n");
}

void	decrease_cycle_before_op(t_cursor *cursor)
{
	if (cursor->cycles_before_op > 0)
	{
		cursor->cycles_before_op--;
		// printf("cycles before op: %d\n", cursor->cycles_before_op);
	}
	printf("IN_FUNC: decrease_cycle_before_op()\n");
}

void	exec_oper(t_cursor *cursor, unsigned char *arena) // 	NEED CHECK FOR EVERY OPERATION
{
	int		code_arg_type[3];

	printf("OPER: %s\n", op_tab[ind(cursor->op_code)].name); //TIME TO CODE OPERATIONS
	if (!(cursor->op_code >= 0x01 && cursor->op_code <= 0x10))
	{
		cursor->cur_position += 1;
		return ;
	}
	if (op_tab[ind(cursor->op_code)].code_type_args)
	{
		code_arg_type[0] = arena[cursor->cur_position + 1] >> 6;
		code_arg_type[1] = (arena[cursor->cur_position + 1] >> 4) & 0x0011;
		code_arg_type[2] = (arena[cursor->cur_position + 1] >> 2) & 0x000011;
		ft_printf("[0] = %#b\n", arena[cursor->cur_position + 1]);
		// if (bad_arg_type(code_arg_type))
		// {
		// 	cursor->cur_position += 1 + 1 + sum_of_sizes(code_arg_type, cursor->op_code);
		// }
		exit(0);
	}
	// check_args(cursor);
	// printf("CODE OF AGRG TYPE: %#x\n", code_arg_type);
	// ft_printf("FT: %#b\n", code_arg_type);
	exit(0);
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
			get_oper_code(cursor, vm->arena);
			decrease_cycle_before_op(cursor);
			if (cursor->cycles_before_op == 0)
				exec_oper(cursor, vm->arena);
			// print_list_of_cursors(vm->cursor);
			cursor = cursor->next;
		}
		cursor = vm->cursor;
		// in_cycle(vm, vm->cursor);
		// if ((vm->cycles_to_die > 0 && vm->num_of_cycles == vm->cycles_to_die)
		// 	|| vm->cycles_to_die <= 0)
		// 	inspection(vm, vm->cursor);
	}
}
