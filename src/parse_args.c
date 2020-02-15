#include "head.h"

void	parsing_dumps(int *ac, char ***av, t_fl *flag)
{
	int i;

	i = 0;
	while (i < *ac && (*av)[i][0] == '-' && (*av)[i][1])
		if (!ft_strcmp((*av)[i] + 1, "d") && i + 1 < *ac && ft_isnumber((*av)[i + 1]))
		{
			flag->d = ft_atoi((*av)[i + 1]);
			i += 2;
		}
		else if (!ft_strcmp((*av)[i] + 1, "dump") && i + 1 < *ac && ft_isnumber((*av)[i + 1]))
		{
			flag->dump = ft_atoi((*av)[i + 1]);
			i += 2;
		}
		else if (!ft_strcmp((*av)[i] + 1, "n") && i + 1 < *ac && ft_isnumber((*av)[i + 1]))
			break ;
		else
			usage();
	(*av) += i;
	(*ac) -= i;
	if (!*ac)
		usage();
}

int		same_id(t_champ *champ, int id)
{
	t_champ *tmp;

	tmp = champ;
	while (tmp)
	{
		if (tmp->id == id)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	set_ids_to_champs(t_vm *vm)
{
	t_champ		*champ;
	static int	ids[4] = {1, 2, 3, 4};

	champ = vm->champ;
	while (champ)
	{
		if (champ->id != 0)
			ids[champ->id - 1] = 0;
		champ = champ->next;
	}
	ft_printf("%d %d %d %d\n", ids[0], ids[1], ids[2], ids[3]);
	champ = vm->champ;
	while (champ)
	{
		if (champ->id == 0)
		{
			if (ids[0] != 0)
				champ->id = ids[0];
			else if (ids[1] != 0)
				champ->id = ids[1];
			else if (ids[2] != 0 || ids[3] != 0)
				champ->id = ids[2] != 0 ? ids[2] : ids[3];
		}
		champ = champ->next;
	}
	champ= vm->champ;
	while (champ)
	{
		ft_printf("id = %d\n", champ->id);
		champ = champ->next;
	}
	// sort_list(vm);
}

void	parsing_args(t_vm *vm, int *ac, char ***av)
{
	int		i;
	int		n;

	parsing_dumps(ac, av, &vm->flag);
	i = 0;
	while (i < *ac)
	{
		if ((*av)[i][0] == '-' && (*av)[i][1])
		{
			if (!ft_strcmp((*av)[i] + 1, "n") && i + 2 < *ac && ft_isnumber((*av)[i + 1]))
			{
				if ((n = ft_atoi((*av)[i + 1])) < 1 ||
						n > MAX_ARGS_NUMBER || same_id(vm->champ, n))
					usage(); // INVALID CHAMP NUMBER
				init_champs(vm, (*av)[i + 2], n);
				i += 3;
				continue ;
			}
			else
				usage();
		}
		init_champs(vm, (*av)[i], 0);
		i++;
	}
	set_ids_to_champs(vm);
}