#include "head.h"

void	error(char *format, void *str)
{
	ft_fprintf(stderr, format, str);
	exit(1);
}

void	malloc_err(void *addr, char *func)
{
	if (!addr)
		error("malloc error in %s\n", func);
}

void	usage(void)
{
	ft_fprintf(stderr, "Usage: ./corewar [-d N -dump N -l -aff] [[-n N]");
	ft_fprintf(stderr, "<champion1.cor>] <...>\n\n");
	ft_fprintf(stderr, "    -l:		turn off live-operation output\n");
	ft_fprintf(stderr, "    -aff:   	turn on aff-operation output\n");
	ft_fprintf(stderr, "    -d N:	dumps memory after N cycles then exists ");
	ft_fprintf(stderr, "(64 octets)\n");
	ft_fprintf(stderr, "    -dump N:	dumps memory after N cycles then ");
	ft_fprintf(stderr, "exists (32 octets)\n");
	ft_fprintf(stderr, "    -n N:	sets the number of next player. ");
	ft_fprintf(stderr, "If non-existent, the player\n\t\twill have the next");
	ft_fprintf(stderr, "available number in the order of the parameters.\n");
	exit(1);
}

void	introduce(t_champ *champ)
{
	t_champ	*tmp;
	int		i;

	tmp = champ;
	i = 1;
	ft_printf("Introducing contestants...\n");
	while (tmp)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
					i, tmp->header.prog_size,
					tmp->header.prog_name, tmp->header.comment);
		i++;
		tmp = tmp->next;
	}
}

void	print_winner(t_vm *vm)
{
	t_champ *champ;
	t_champ *last;

	champ = vm->champ;
	while (champ)
	{
		if (champ->id == vm->last_live)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n",
						champ->id, champ->header.prog_name);
			return ;
		}
		if (!champ->next)
			last = champ;
		champ = champ->next;
	}
	ft_printf("Contestant %d, \"%s\", has won !\n",
					last->id, last->header.prog_name);
}

void	print_dump(t_fl flag, unsigned char *arena)
{
	int i;
	int j;
	int dump;

	dump = 64;
	if (flag.dump)
		dump = 32;
	i = 0;
	j = 1;
	while (i < MEM_SIZE)
	{
		if (!(i % dump))
			ft_printf("%.4p : ", (j - 1) * dump);
		ft_printf("%02x ", arena[i]);
		if (i == j * dump - 1)
		{
			ft_printf("\n");
			j += 1;
		}
		i++;
	}
	exit(0);
}
