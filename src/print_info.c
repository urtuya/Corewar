#include "head.h"

void	print_info(t_vm *vm)
{
	while (vm->champ)
	{
		ft_fprintf(stderr, "ID: %d\n", vm->champ->id);
		ft_fprintf(stderr, "NAME: %s\n", vm->champ->header.prog_name);
		ft_fprintf(stderr, "PROG SIZE: %d\n", vm->champ->header.prog_size);
		ft_fprintf(stderr, "COMMENT: \"%s\"\n\n", vm->champ->header.comment);
		vm->champ = vm->champ->next;
	}
	ft_fprintf(stderr, "NUMBER OF PLAYERS: %d\n", vm->players_num);
}

void	print_arena(unsigned char *arena, t_champ *champ, int next_byte)
{
	int i;
	int j;
	int k;
	int until_next_byte;

	i = 0;
	k = 0;
	until_next_byte = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			if (champ && k < champ->header.prog_size + until_next_byte)
				ft_fprintf(stderr, "{magenta}%02x  ", arena[k]);
			else if (k < until_next_byte + next_byte)
				ft_fprintf(stderr, "%02x  ", arena[k]);
			if (k != MEM_SIZE - 1 && k == until_next_byte - 1 + next_byte)
			{
				champ = champ->next;
				until_next_byte += next_byte;
			}
			j++;
			k++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_arena_2(unsigned char *arena, int addr, int len)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	// ft_printf("{red}here\n");
	while (i < 64)
	{
		j = 0;
		ft_printf("0x%04x : ", i* 64);
		while (j < 64)
		{
			if (k == addr)
			{
				ft_printf("{red}%02x ", arena[k]);
				addr += (addr < len - 1 ? 1 : 0);
			}
			else
				ft_printf("%02x ", arena[k]);
			j ++;
			k++;
		}
		ft_printf("\n");
		i++;
	}
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

void	print_list_of_cursors(t_cursor *cursor)
{
	t_cursor *cursors;

	ft_printf("LIST OF CURSORS\n");
	cursors = cursor;
	while (cursor)
	{
		ft_printf("ID: %d\n", cursor->id);
		ft_printf("CUR_POS: %d\n", cursor->cur_position);
		// ft_printf("OP_CODE: %d\n", cursor->op_code);
		// ft_printf("CYCLES TO EXEC: %d\n", cursor->cycles_before_op);
		// ft_printf("{red}CHAMP: %s\n", cursor->CHAMP_NAME);
		if (cursor->next)
		{
			ft_printf("|\n");
			ft_printf("V\n");
		}
		cursor = cursor->next;
	}
}

void	print_registers(int *registers)
{
	int i;

	i = 0;
	while (i < 16)
	{
		ft_printf("r[%d] = %d  ", i + 1, registers[i]);
		i++;
	}
	ft_printf("\n");
}