#include "head.h"

void	set_to_arena(unsigned char *arena, int arg)
{
	*(arena) = (arg & 0xff000000) >> 24;
	*(arena + 1) = (arg & 0x00ff0000) >> 16;
	*(arena + 2) = (arg & 0x0000ff00) >> 8;
	*(arena + 3) = (arg & 0x000000ff);

}

void	op_st(t_cursor *cursor, unsigned char *arena)
{
	int		addr;
	int		arg[2];

	ft_printf("{blue}OP_ST\n");
	arg[0] = arena[ADDR(cursor->cur_position + 2)];
	
	if (IS_REG(cursor->arg_type[1]))
	{
		// print_registers(cursor->r);
		arg[1] = *(arena + ADDR(cursor->cur_position + 3));
		cursor->r[arg[1] - 1] = cursor->r[arg[0] - 1]; // - 1 потому что счет с нуля
		// print_registers(cursor->r);
		ft_printf("LOL\n");
	}
	else if (IS_IND(cursor->arg_type[1]))
	{
		arg[1] = bin2int(arena + ADDR(cursor->cur_position + 3), IND_SIZE);
		addr = cursor->cur_position + (arg[1] % IDX_MOD);

		set_to_arena(arena + addr, cursor->r[arg[0] - 1]);
		print_arena_2(arena);
	}
}