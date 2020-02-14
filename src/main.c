#include "../inc/head.h"

int		check_extention(char *file)
{
	char *tmp;

	tmp = ft_strstr(file, ".cor");
	if (!tmp || ft_strcmp(tmp, ".cor"))
		return (0);
	return (1);
}
//-------------------------------LIST  OF CHAMPS

// t_op op_tab[17];


int		main(int argc, char **argv)
{
	t_vm		*vm;
	char *str;

	vm = NULL;
	if (argc < 2)
		usage();
	// parsing_args(vm, argc - 1, argv + 1);
	else if (argc > MAX_ARGS_NUMBER + 1)
		error("%s\n", "Too many champions");

	vm = init_vm();
	init_champs(argc - 1, argv + 1, vm);

	introduce(vm->champ);
	
	init_arena(vm);
	vm->cursor = init_first_cursors(vm);
	in_cycle(vm);

	printf("NUM of cycles: %d\n", vm->num_of_cycles);
	printf("CYCLES TO DIE: %d\n", vm->cycles_to_die);
	print_arena_2(vm->arena, -1, -1);

	return (0);
}

