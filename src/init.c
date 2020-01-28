#include "../inc/head.h"

t_vm	*init_vm(void)
{
	t_vm *vm;

	malloc_err((vm = (t_vm*)malloc(sizeof(t_vm))), "init_vm");
	vm->champ = NULL;
	vm->flag = (t_fl){0, 0};
	vm->players_num = 0;
	vm->last_live = 0;
	vm->num_of_cycles = 0;
	vm->nbr_live = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->checks = 0; 
	vm->num_of_cursors = 0;
	vm->cursor = NULL;

	vm->was_inspected = 0;

	return (vm);
}

void	add_champ(t_champ **champ_list, t_champ *champ_to_add)
{
	t_champ *new;

	if (champ_list && champ_to_add)
	{
		if (*champ_list)
		{
			new = *champ_list;
			while (new->next)
				new = new->next;
			new->next = champ_to_add;
		}
		else
			*champ_list = champ_to_add;
	}
}


//-----------------------------LIST OF CHAMPS

void	init_champs(int argc, char **argv, t_vm *vm)
{
	t_champ *champ;
	size_t i;

	malloc_err((champ = (t_champ*)malloc(sizeof(t_champ))), "init_champs");
	vm->champ = champ;
	vm->champ_head = vm->champ; //	THIS IS NOT GUT
	i = 0;
	while (i < argc)
	{
		champ->id = i + 1;
		check_valid(argv[i], champ);
		if (i != argc - 1)
			malloc_err((champ->next = (t_champ*)malloc(sizeof(t_champ))), "init_champs()");
		else
			champ->next = NULL;
		champ = champ->next;
		vm->players_num++;
		i++;
	}
	vm->next_byte = MEM_SIZE / vm->players_num;
	vm->champ = vm->champ_head;
}

t_cursor	*create_cursor(t_cursor **cursor)
{
	t_cursor *new;

	malloc_err((new = (t_cursor*)malloc(sizeof(t_cursor))), "create_cursor");
	new->next = *cursor;
	(*cursor)->prev = new;
	return (new);
	
}

void		init_cursors(t_vm *vm, t_cursor *new, t_cursor *old)
{
	new->id = ++vm->num_of_cursors;
	new->carry = old->carry;
	new->op_code = 0;
	new->last_live_cycle_nbr = old->last_live_cycle_nbr;
	new->cycles_before_op = 0;
	new->cur_position = old->cur_position;
	new->bytes_to_next_op = 0;
	ft_memcpy(new->r, old->r, 16);
	new->CHAMP_NAME = ft_strdup(old->CHAMP_NAME);
	old->prev = new;
}

t_cursor	*init_first_cursors(t_vm *vm)
{
	t_cursor	*new_curs;
	t_champ		*champ;
	int			addr;

	new_curs = NULL;
	addr = 0;
	champ = vm->champ;
	while (champ)
	{
		if (!new_curs)
		{
			new_curs = (t_cursor*)malloc(sizeof(t_cursor));
			new_curs->next = NULL;
			new_curs->prev = NULL;
		}
		else
			new_curs = create_cursor(&new_curs);
		new_curs->id = ++vm->num_of_cursors;
		new_curs->carry = 0;
		new_curs->op_code = 0;
		new_curs->last_live_cycle_nbr = 0;
		new_curs->cycles_before_op = 0;
		new_curs->cur_position = champ->start_from;
		new_curs->bytes_to_next_op = 0;
		ft_bzero(new_curs->r, 16);
		new_curs->r[0] = -champ->id;
		new_curs->CHAMP_NAME = ft_strdup(champ->header.prog_name);
		printf("NEW_CURS ID: %zu\n", new_curs->id);
		champ = champ->next;
	}
	return (new_curs);
}