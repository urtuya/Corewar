#include "../inc/head.h"

t_vm	*init_vm(void)
{
	t_vm *vm;

	malloc_err((vm = (t_vm*)malloc(sizeof(t_vm))), "init_vm");
	vm->champ = NULL;
	vm->players_num = 0;
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

void	init_champs(int argc, char **argv, t_vm *vm)
{
	t_champ *champ;
	int i;

	malloc_err((champ = (t_champ*)malloc(sizeof(t_champ))), "init_champs");
	vm->champ = champ;
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
}

void	print_info(t_vm *vm)
{
	while (vm->champ)
	{
		printf("ID: %d\n", vm->champ->id);
		printf("NAME: %s\n", vm->champ->header.prog_name);
		printf("PROG SIZE: %d\n", vm->champ->header.prog_size);
		printf("COMMENT: \"%s\"\n\n", vm->champ->header.comment);
		vm->champ = vm->champ->next;
	}
	printf("NUMBER OF PLAYERS: %d\n", vm->players_num);
}