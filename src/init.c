#include "../inc/head.h"

void	add_new_champ(t_vm *vm, int id, char *file)
{
	t_champ *new;
	t_champ *tmp;

	if (!vm->champ)
	{
		malloc_err((vm->champ = (t_champ*)malloc(sizeof(t_champ))), "add_new_champ");
		vm->champ->id = id;

	}
}

t_vm	*init_vm(void)
{
	t_vm *vm;

	malloc_err((vm = (t_vm*)malloc(sizeof(t_vm))), "init_vm");
	vm->champ = NULL;
	vm->flag = (t_fl){-1, 0, 0};
	vm->players_num = 0;
	vm->last_live = 0;
	vm->num_of_cycles = 0;
	vm->nbr_live = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->checks = 0; 
	vm->num_of_cursors = 0;
	vm->cursor = NULL;
	// vm->are_alive = 0;
	vm->cycles_before_check = CYCLE_TO_DIE;
	init_operations(vm);
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

// void	init_champs(int argc, char **argv, t_vm *vm)
// {
// 	t_champ *champ;
// 	size_t i;

// 	malloc_err((champ = (t_champ*)malloc(sizeof(t_champ))), "init_champs");
// 	vm->champ = champ;
// 	i = 0;
// 	while (i < argc)
// 	{
// 		champ->id = i + 1;
// 		check_valid(argv[i], champ);
// 		if (i != argc - 1)
// 			malloc_err((champ->next = (t_champ*)malloc(sizeof(t_champ))), "init_champs()");
// 		else
// 			champ->next = NULL;
// 		champ = champ->next;
// 		vm->players_num++;
// 		i++;
// 	}
// 	vm->next_byte = MEM_SIZE / vm->players_num;
// }

void	init_champs(t_vm *vm, char *file, int id, int flag)
{
	t_champ		*champ;
	t_champ		*new;
	static int	max_id = 1;

	if (!vm->champ)
	{
		malloc_err((vm->champ = (t_champ*)malloc(sizeof(t_champ))), "init_champs");
		champ = vm->champ;
	}
	else
	{
		champ = vm->champ;
		while (champ->next)
			champ = champ->next;
		malloc_err((new = (t_champ*)malloc(sizeof(t_champ))), "init_champs");
		champ->next = new;
		champ = champ->next;
	}
	champ->id = id;
	max_id = id > max_id ? id : max_id;
	champ->next = NULL;
	check_valid(file, champ);
	vm->players_num++;
	if (flag && max_id > vm->players_num)
			usage();
}


t_cursor	*create_cursor(t_cursor **cursor)
{
	t_cursor *new;

	malloc_err((new = (t_cursor*)malloc(sizeof(t_cursor))), "create_cursor");
	new->next = *cursor;
	(*cursor)->prev = new;
	new->prev = NULL;
	return (new);
	
}

void		init_cursor(t_cursor *new, size_t *num, t_champ *champ)
{
	new->id = ++(*num);
	new->carry = 0;
	new->op_code = 0;
	new->last_live_cycle_nbr = 0;
	new->cycles_before_op = 0;
	new->cur_position = champ->start_from;
	new->bytes_to_next_op = 0;
	ft_bzero(new->arg_type, sizeof(new->arg_type));
	ft_bzero(new->r, sizeof(new->r));
	new->r[0] = -champ->id;
}

t_cursor	*init_first_cursors(t_vm *vm)
{
	t_cursor	*new_curs;
	t_champ		*champ;

	new_curs = NULL;
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
		init_cursor(new_curs, &vm->num_of_cursors, champ);
		champ = champ->next;
	}
	// vm->are_alive = vm->num_of_cursors;
	return (new_curs);
}

