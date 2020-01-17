#include "../inc/head.h"

void	malloc_err(void *addr, char *func)
{
	if (!addr)
		error("malloc error in %s\n", func);
}

void	usage(void)
{
	printf("Usage: ./corewar scdvfbgkdfgnv,ldjvkzsmdvnxfdgb\n");
	exit(0);
}

void	error(char *format, char *str)
{
	fprintf(stderr, format, str);
	exit (1);
}

int		check_extention(char *file)
{
	char *tmp;

	tmp = ft_strstr(file, ".cor");
	if (!tmp || ft_strcmp(tmp, ".cor"))
		return (0);
	return (1);
}



int		main(int argc, char **argv)
{
	t_vm		*vm;

	vm = NULL;
	if (argc < 2)
		usage();
	else if (argc > MAX_ARGS_NUMBER + 1)
		error("%s\n", "Too many champions");
	vm = init_vm();
	init_champs(argc - 1, argv + 1, vm);

	print_info(vm);

	return (0);
}

