#include "head.h"

t_cursor	*remove_one(t_cursor **head, t_cursor **curr)
{
	t_cursor *tmp;

	tmp = NULL;
	if (*curr == *head)
	{
		*head = (*head)->next;
		if (*head)
			(*head)->prev = NULL;
	}
	else
	{
		if ((*curr)->next)
			(*curr)->next->prev = (*curr)->prev;
		if ((*curr)->prev)
			(*curr)->prev->next = (*curr)->next;
	}
	tmp = (*curr)->next;
	free(*curr);
	return (tmp);
}

void		remove_dead_cursors(t_vm *vm, t_cursor *cursor)
{
	t_cursor *curr;
	t_cursor *tmp;

	tmp = NULL;
	curr = vm->cursor;
	while (curr)
		if (vm->num_of_cycles - curr->last_live_cycle_nbr >= vm->cycles_to_die
				|| vm->cycles_to_die <= 0)
			curr = remove_one(&vm->cursor, &curr);
		else
			curr = curr->next;
}

void		inspection(t_vm *vm, t_cursor *cursor)
{
	vm->checks++;
	remove_dead_cursors(vm, cursor);
	if (vm->nbr_live >= NBR_LIVE || vm->checks == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	if (!vm->cursor)
		ft_printf("NBR LIVE: %d\n", vm->nbr_live);
	vm->nbr_live = 0;
	vm->cycles_before_check = vm->cycles_to_die;
}

int			size_arg_type(int arg, int op_code)
{
	t_op	*op_tab;

	op_tab = t_op_tab();
	if (arg == T_REG)
		return (1);
	else if (arg == T_IND)
		return (2);
	else if (arg == T_DIR)
		return (op_tab[op_code].size_of_t_dir ? 2 : 4);
	return (0);
}

int			check_arg_type(t_cursor *cursor)
{
	int		i;
	int		ret;
	t_op	*op_tab;

	i = 0;
	ret = 1;
	op_tab = t_op_tab();
	cursor->bytes_to_next_op = 1 + (op_tab[cursor->op_code].code_type_args ?
																		1 : 0);
	while (i < op_tab[cursor->op_code].arg_num)
	{
		if ((cursor->arg_type[i] & op_tab[cursor->op_code].arg[i]) == 0)
			ret = 0;
		cursor->bytes_to_next_op += size_arg_type(cursor->arg_type[i],
														cursor->op_code);
		i++;
	}
	return (ret);
}

int			check_registers(t_cursor *cursor, unsigned char *arena)
{
	int		i;
	int		bytes_to_jmp;
	int		reg;
	t_op	*op_tab;

	op_tab = t_op_tab();
	i = 0;
	bytes_to_jmp = ft_addr(cursor->cur_position + 1 +
			(op_tab[cursor->op_code].code_type_args ? 1 : 0));
	while (i < op_tab[cursor->op_code].arg_num)
	{
		if (cursor->arg_type[i] == T_REG)
		{
			reg = bin2int(arena + ft_addr(bytes_to_jmp), 1);
			if (reg < 1 || reg > REG_NUMBER)
				return (0);
		}
		bytes_to_jmp += size_arg_type(cursor->arg_type[i], cursor->op_code);
		i++;
	}
	return (1);
}
