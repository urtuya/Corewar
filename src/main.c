#include "../inc/head.h"

/* //NO EXTENTION FOR CHAMPION FILE! JUST VALID OF BYTECODE! 
int		check_extention(char *file)
{
	char *tmp;

	tmp = ft_strstr(file, ".cor");
	if (!tmp || ft_strcmp(tmp, ".cor"))
		return (0);
	return (1);
}
*/

int		main(int argc, char **argv)
{
	t_vm		*vm;
	char *str;

	vm = NULL;
	if (argc < 2)
		usage();
	
	argc--;
	argv++;
	// else if (argc > MAX_ARGS_NUMBER + 1)
	// 	error("%s\n", "Too many champions");

	vm = init_vm();
	parsing_args(vm, &argc, &argv);
	introduce(vm->champ);
	init_arena(vm);
	vm->cursor = init_first_cursors(vm);
	in_cycle(vm);


	// printf("NUM of cycles: %d\n", vm->num_of_cycles);
	// printf("CYCLES TO DIE: %d\n", vm->cycles_to_die);
	// print_winner(vm->champ, vm->last_live);

	return (0);
}

