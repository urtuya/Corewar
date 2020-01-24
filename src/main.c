#include "../inc/head.h"

void	error(char *format, void *str)
{
	ft_fprintf(stderr, format, str);
	exit (1);
}


void	malloc_err(void *addr, char *func)
{
	if (!addr)
		error("malloc error in %s\n", func);
}

void	usage(void)
{
	ft_fprintf(stderr, "Usage: ./corewar scdvfbgkdfgnv,ldjvkzsmdvnxfdgb\n");
	exit(1);
}

int		check_extention(char *file)
{
	char *tmp;

	tmp = ft_strstr(file, ".cor");
	if (!tmp || ft_strcmp(tmp, ".cor"))
		return (0);
	return (1);
}
//-------------------------------LIST  OF CHAMPS
void	print_info(t_vm *vm)
{
	while (vm->champ)
	{
		ft_fprintf(stderr, "ID: %d\n", vm->champ->id);
		ft_fprintf(stderr, "NAME: %s\n", vm->champ->header.prog_name);
		ft_fprintf(stderr, "PROG SIZE: %d\n", vm->champ->header.prog_size);
		ft_fprintf(stderr, "COMMENT: \"%s\"\n\n", vm->champ->header.comment);
		vm->champ = vm->champ->next;
	}
	ft_fprintf(stderr, "NUMBER OF PLAYERS: %d\n", vm->players_num);
}

int		main(int argc, char **argv)
{
	t_vm		*vm;
	char *str;

	vm = NULL;
	if (argc < 2)
		usage();
	else if (argc > MAX_ARGS_NUMBER + 1)
		error("%s\n", "Too many champions");
	vm = init_vm();
	init_champs(argc - 1, argv + 1, vm);


	init_arena(vm);
	start(vm);
	print_info(vm);

	return (0);
}

