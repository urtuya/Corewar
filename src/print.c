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


void	introduce(t_champ *champ)
{
	t_champ *tmp;
	int i;

	tmp = champ;
	i = 1;
	ft_printf("Introducing contestants...\n");
	while (tmp)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i, tmp->header.prog_size, tmp->header.prog_name, tmp->header.comment);
		i++;
		tmp = tmp->next;
	}
}

void	print_winner(t_champ *chmp, int last_live)
{
	t_champ *champ;

	champ = chmp;
	// ft_printf("LAST LIVE: %d\n", last_live);
	while (champ)
	{
		if (champ->id == last_live)
		{
			ft_printf("Contestant %d, \"%s\", has won !\n", champ->id, champ->header.prog_name);
			return ;
		}
		champ = champ->next;
	}
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
			printf("%.4p : ", (j - 1) * dump);
		printf("%02x ", arena[i]);
		if (i == j * dump - 1)
		{
			printf("\n");
			j += 1;
		}
		i++;
	}
	exit(0);
}