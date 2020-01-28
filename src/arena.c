#include "head.h"

//------------------LIST OF CHAMPS
void	init_arena(t_vm *vm)
{
	size_t			i;
	t_champ			*champ;
	unsigned char	*arena;

	i = 0;
	champ = vm->champ;
	arena = vm->arena;
	ft_bzero(vm->arena, MEM_SIZE);
	while (champ)
	{
		ft_memcpy(arena, champ->exec_code, champ->header.prog_size);
		champ->start_from = i;
		champ = champ->next;
		i += vm->next_byte;
		arena += vm->next_byte;
	}
}

