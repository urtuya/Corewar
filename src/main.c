#include "../inc/head.h"

int		ft_addr(int value)
{
	value = value % MEM_SIZE;
	if (value < 0)
		value += MEM_SIZE;
	return (value);
}

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
	introduce(vm->champ);

	init_arena(vm);
	start(vm);

	printf("NUM of cycles: %d\n", vm->num_of_cycles);
	printf("CYCLES TO DIE: %d\n", vm->cycles_to_die);
	// printf("NO MORE ALIVE\n");
	print_arena_2(vm->arena, -1, -1);
	// print_info(vm);
	// print_list_of_cursors(vm->cursor);

	return (0);
}

