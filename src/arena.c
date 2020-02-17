#include "head.h"

//------------------LIST OF CHAMPS
void	init_arena(t_vm *vm)
{
	size_t			i;
	t_champ			*champ;
	unsigned char	*arena;
	int				next_byte;

	i = 0;
	champ = vm->champ;
	next_byte = MEM_SIZE / vm->players_num;
	arena = vm->arena;
	ft_bzero(vm->arena, MEM_SIZE);
	while (champ)
	{
		ft_memcpy(arena, champ->exec_code, champ->header.prog_size);
		champ->start_from = i;
		champ = champ->next;
		i += next_byte;
		arena += next_byte;
	}
}

