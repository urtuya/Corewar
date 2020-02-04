#include "head.h"

t_cursor *kill_cursors(t_cursor *cursor)
{
	return (NULL);
}

t_cursor *kill_single_cursor(t_cursor *cursor)
{
	t_cursor *tmp;

	tmp = cursor->next;
	if (cursor->prev)
		cursor->prev->next = cursor->next;
	ft_strdel(&cursor->CHAMP_NAME);
	free(cursor);
	cursor = NULL;
	return (tmp);
}

// ALL FROM COOKBOOK 
void	inspection(t_vm *vm, t_cursor *cursor)
{
	t_cursor *current;

	if (vm->cycles_to_die <= 0)
	{
		cursor = kill_cursors(cursor); // 1 for 1st reason, 2 for 2nd reason(kill all cursors)
	}
	else
	{
		current = cursor;
		while (current)
		{
			if (vm->num_of_cycles - cursor->last_live_cycle_nbr >= vm->cycles_to_die)
				current = kill_single_cursor(current);
			else
				current = current->next;
		}
		cursor = current;
	}
	if (vm->nbr_live >= NBR_LIVE || vm->checks == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	vm->was_inspected = 1;
	vm->checks++;
	
}
int		check_arg_type(t_cursor *cursor)
{
	int i;
	int ret;

	i = 0;
	ret = 1;
	cursor->bytes_to_next_op = 1 + (op_tab[cursor->op_code].code_type_args ? 1 : 0);
	while (i < op_tab[cursor->op_code].arg_num)
	{
		if ((cursor->arg_type[i] & op_tab[cursor->op_code].arg[i]) == 0)
			ret = 0;
		cursor->bytes_to_next_op += size_arg_type(cursor->arg_type[i], cursor->op_code);
		i++;
	}
	ft_printf("%s", "\n\n");
	return (ret);
}


int		size_arg_type(int arg, int op_code) // return size of arg type
{
	if (IS_REG(arg)) // YETO GENIAL'NO
		return (1);
	else if (IS_IND(arg))
		return (2);
	else if (IS_DIR(arg))
		return (op_tab[op_code].size_of_t_dir ? 2 : 4);
	return (0);
}

int		check_registers(t_cursor *cursor, unsigned char *arena)
{
	int i;
	int	bytes_to_jmp;
	int	reg;

	ft_printf("bytes_to_next_op = %d\n", cursor->bytes_to_next_op);
	i = 0;
	bytes_to_jmp = (cursor->cur_position + 1 + (op_tab[cursor->op_code].code_type_args ? 1 : 0)) % MEM_SIZE;
	while (i < op_tab[cursor->op_code].arg_num)
	{
		if (IS_REG(cursor->arg_type[i]))
		{
			reg = bin2int(arena + bytes_to_jmp, 1);
			ft_printf("IS_REG: %d\n", reg);
			if (reg < 1 || reg > 16)
			{
				ft_fprintf(stderr, "reg is not GUT\n");
				return (0);
			}
		}
		bytes_to_jmp += size_arg_type(cursor->arg_type[i], cursor->op_code);
		ft_printf("bytes_to_jmp = %d\n", bytes_to_jmp); 
		i++;
	}
	return (1);
}