#include "head.h"

// void	parsing_args(t_vm *vm, int ac, char **av)
// {
// 	int i;

// 	i = 0;
// 	while (i < ac)
// 	{
// 		if (*av[i] == '-')
// 		{
// 			if (!ft_strcmp(av[i] + 1, "d"))
// 			{
// 				if (i + 1 < ac && ft_isnumber(av[i + 1]) && *av[i + 1] != '-')
// 					vm->flag.d = ft_atoi(av[i + 1], 10);
// 			}
// 			else if (!ft_strcmp(av[i] + 1, "dump"))
// 			{
// 				if (i + 1 < ac && ft_isnumber(av[i + 1]) && *av[i + 1] != '-')
// 					vm->flag.dump = ft_uintmaxtoa(av[i + 1], 10);
// 			}
// 		}
// 		i++;
// 	}
// }