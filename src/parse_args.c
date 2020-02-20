#include "head.h"

void	set_dump_flag(int *flag1, int *flag2)
{
	*flag1 = 1;
	if (*flag2 > 0)
		*flag2 = 0;
}

void	d_flag(t_fl *flag, int num, char *str, int *i)
{
	flag->num = num;
	if (flag->num < 0)
		exit(0);
	if (!(ft_strcmp(str, "dump")))
		set_dump_flag(&flag->dump, &flag->d);
	else
		set_dump_flag(&flag->d, &flag->dump);
	*i += 2;
}

void	live_aff_flag(t_fl *flag, int *i, int q)
{
	if (!q)
		flag->live = 0;
	else if (q == 1)
		flag->aff = 1;
	*i += 1;
}

void	parsing_dumps(int *ac, char ***av, t_fl *flag)
{
	int i;

	i = 0;
	while (i < *ac && (*av)[i][0] == '-' && (*av)[i][1])
		if ((!ft_strcmp((*av)[i] + 1, "d") || !ft_strcmp((*av)[i] + 1, "dump"))\
			&& i + 2 < *ac && ft_isnumber((*av)[i + 1]))
			d_flag(flag, ft_atoi((*av)[i + 1]), (*av)[i] + 1, &i);
		else if (!ft_strcmp((*av)[i] + 1, "l"))
			live_aff_flag(flag, &i, 0);
		else if (!ft_strcmp((*av)[i] + 1, "aff"))
			live_aff_flag(flag, &i, 1);
		else if (!ft_strcmp((*av)[i] + 1, "n")
				&& i + 1 < *ac && ft_isnumber((*av)[i + 1]))
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

void	sorting(t_champ **head, t_champ *new)
{
	t_champ *curr;

	if (!*head || (*head)->id >= new->id)
	{
		new->next = *head;
		*head = new;
		return ;
	}
	curr = *head;
	while (curr->next && curr->next->id < new->id)
		curr = curr->next;
	new->next = curr->next;
	curr->next = new;
}

void	ins_sort(t_champ **head, int num)
{
	t_champ *next;
	t_champ *sorted;
	t_champ *curr;

	if (num < 2)
		return ;
	sorted = NULL;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		sorting(&sorted, curr);
		curr = next;
	}
	*head = sorted;
}

void	args_number(int num)
{
	if (num > MAX_ARGS_NUMBER)
		error("Too many champions\n", "");
}

void	set_ids_to_champs(t_vm *vm)
{
	t_champ		*champ;
	static int	ids[4] = {1, 2, 3, 4};

	args_number(vm->players_num);
	champ = vm->champ;
	while (champ)
	{
		if (champ->id != 0)
			ids[champ->id - 1] = 0;
		champ = champ->next;
	}
	champ = vm->champ;
	while (champ)
	{
		if (champ->id == 0)
		{
			if (ids[0] != 0 || ids[1] != 0)
				champ->id = ids[0] != 0 ? ids[0] : ids[1];
			else if (ids[2] != 0 || ids[3] != 0)
				champ->id = ids[2] != 0 ? ids[2] : ids[3];
			ids[champ->id - 1] = 0;
		}
		champ = champ->next;
	}
}

void	flag_n(t_vm *vm, int num)
{
	// if ((n = ft_atoi((*av)[i + 1])) < 1 ||
	// 		n > MAX_ARGS_NUMBER || same_id(vm->champ, n))
	// 	usage(); // INVALID CHAMP NUMBER
	if (num < 1 || num > MAX_ARGS_NUMBER || same_id(vm->champ, num))
		error("Invalid champion number\n", ""); // or usage
}

void	parsing_args(t_vm *vm, int *ac, char ***av)
{
	int				i;
	int				n;

	parsing_dumps(ac, av, &vm->flag);
	i = -1;
	while (++i < *ac)
	{
		if ((*av)[i][0] == '-' && (*av)[i][1])
		{
			if (!ft_strcmp((*av)[i] + 1, "n") &&
				i + 2 < *ac && ft_isnumber((*av)[i + 1]))
			{
				flag_n(vm, (n = ft_atoi((*av)[i + 1])));
				init_champs(vm, (*av)[i + 2], n, i + 3 >= *ac);
				i += 2;
				continue ;
			}
			else
				usage();
		}
		init_champs(vm, (*av)[i], 0, i + 1 >= *ac);
	}
	set_ids_to_champs(vm);
	ins_sort(&vm->champ, vm->players_num);
}
