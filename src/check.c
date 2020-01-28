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

int		sum_of_sizes(int *types, int op_code)
{
	int sum;
	int	t_dir_size;

	sum = 0;
	t_dir_size = (op_tab[ind(op_code)].size_of_t_dir) ? 2 : 4;
	// if 
	
	return (0);
}