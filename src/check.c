#include "head.h"

void	inspection(t_vm *vm, t_cursor *cursor)
{
	t_cursor *curr;
	t_cursor *tmp;
	static int count = 0;

	count ++;
	ft_printf("{cyan}INSPECTION HERE\n");
	// print_list_of_cursors(cursor/);
	// ft_printf("ARE ALIVE: %d\n", vm->are_alive);
	ft_printf("{cyan}num of cycles: %d\n", vm->num_of_cycles);

	tmp = NULL;
	vm->checks++;
	vm->nbr_live = 0;
	curr = vm->cursor;
	ft_printf("DEAD:\n");
	while (curr)
	{
		if (vm->num_of_cycles - curr->last_live_cycle_nbr >= vm->cycles_to_die || vm->cycles_to_die <= 0)
		{
			ft_printf("id: %d\n", curr->id);
			vm->are_alive--;
			if (curr == vm->cursor)
			{
				vm->cursor = vm->cursor->next;
				if (vm->cursor)
					vm->cursor->prev = NULL;
			}
			else
			{
				if (curr->next)
					curr->next->prev = curr->prev;
				if (curr->prev)
					curr->prev->next = curr->next;
			}
			tmp = curr->next;
			free(curr);
			curr = tmp;
		}
		else
			curr = curr->next;
	}
	if (vm->nbr_live >= NBR_LIVE || vm->checks == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	vm->cycles_before_check = vm->cycles_to_die;
		if (count == 2)
	exit(0);
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

	// if (cursor->bytes_to_next_op == 8)
	// 	exit(0);
	// printf("\n\n");
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

	ft_printf("[red}here\n");
	// ft_printf("bytes_to_next_op = %d\n", cursor->bytes_to_next_op);
	i = 0;
	bytes_to_jmp = (cursor->cur_position + 1 + (op_tab[cursor->op_code].code_type_args ? 1 : 0)) % MEM_SIZE;
	while (i < op_tab[cursor->op_code].arg_num)
	{
		if (IS_REG(cursor->arg_type[i]))
		{
			reg = bin2int(arena + ft_addr(bytes_to_jmp), 1);
			// ft_printf("IS_REG: %d\n", reg);
			if (reg < 1 || reg >= REG_NUMBER)
			{
				// ft_fprintf(stderr, "reg is not GUT\n");
				return (0);
			}
		}
		bytes_to_jmp += size_arg_type(cursor->arg_type[i], cursor->op_code);
		// ft_printf("bytes_to_jmp = %d\n", bytes_to_jmp); 
		i++;
	}
	return (1);
}
