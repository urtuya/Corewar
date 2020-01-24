#include "head.h"

void	set_exec_code(unsigned char *arena, int size)
{
	unsigned char *tmp;
	int i;

	i = 0;
	tmp = arena;

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

//------------------LIST OF CHAMPS
void	init_arena(t_vm *vm)
{
	int	next_byte;
	int i;
	unsigned char *arena;

	i = 0;
	arena = vm->arena;
	ft_bzero(vm->arena, MEM_SIZE);
	next_byte = MEM_SIZE / vm->players_num;
	while (vm->champ)
	{
		ft_memcpy(arena, vm->champ->exec_code, vm->champ->header.prog_size);
		vm->champ = vm->champ->next;
		arena += next_byte;
	}
	vm->champ = vm->champ_head;
	print_arena(vm->arena, vm->champ, next_byte);

}


//---------------------------------ARRAY OF CHAMPS
// void	init_arena(t_vm *vm)
// {
// 	int	next_byte;
// 	int i;

// 	ft_bzero(vm->arena, MEM_SIZE);
// 	next_byte = MEM_SIZE / vm->players_num;
// 	i = 0;
// 	while (i < vm->players_num)
// 	{
// 		ft_memcpy(vm->arena, vm->champ[i]->exec_code);
// 	}
// }