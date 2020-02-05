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

t_op op_tab[17];


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
	// print_arena(vm->arena, vm->champ, vm->next_byte);
	// set_to_arena(vm->arena + 4094, 12);
	// print_arena_2(vm->arena, 4094, 4100);
	start(vm);
	// print_info(vm);

	// printf("OP_TAB: op_tab[3]= %d (%s)\n", op_tab[3].cycles_to_exec, "add");
	
	// int args[3] = {2, 3, 5};
	
	return (0);
}

