#include "../inc/head.h"

t_vm	*init_vm(void)
{
	t_vm *vm;

	malloc_err((vm = (t_vm*)malloc(sizeof(t_vm))), "init_vm");
	vm->champ = NULL;
	vm->flag = (t_fl){0, 0};
	vm->players_num = 0;
	vm->last_live = 0;
	vm->cycles = 0;
	vm->nbr_live = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->max_checks = 0;
	vm->cursor = NULL;
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
	int i;

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
	vm->champ = vm->champ_head;
}

t_cursor	*create_cursor(t_cursor **cursor)
{
	t_cursor *new;

	malloc_err((new = (t_cursor*)malloc(sizeof(t_cursor))), "create_cursor");
	new->next = *cursor;
	return (new);
	
}


void		init_cursors(t_vm *vm)
{
	t_cursor	*cursor;
	int			i;
	int			next_byte;
	t_cursor	*head;

	// malloc_err((cursor = (t_cursor*)malloc(sizeof(t_cursor))), "init_cursors");
	// vm->cursor = cursor;
	cursor = NULL;
	next_byte = 0;
	i = 0;
	while (vm->champ)
	{
		if (!cursor)
		{
			malloc_err((cursor = (t_cursor*)malloc(sizeof(t_cursor))), "init_cursors");
			cursor->next = NULL;
		}
		else
			cursor = create_cursor(&cursor);
		vm->cursor = cursor;
		cursor->id = i + 1;
		cursor->carry = 0;
		cursor->op_code = 0;
		cursor->last_live_cycle_nbr = 0;
		cursor->cycle_num = -1;
		cursor->cur_addr = next_byte;
		cursor->bytes_to_get = -1;
		ft_bzero(cursor->r, 16);
		cursor->r[0] = -vm->champ->id;
		cursor->CHAMP_NAME = ft_strdup(vm->champ->header.prog_name);
		vm->champ = vm->champ->next;
		
		i++;
	}
	vm->cursor = cursor;
}

