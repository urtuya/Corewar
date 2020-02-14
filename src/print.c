#include "head.h"

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