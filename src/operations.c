#include "head.h"

void	op_st(t_cursor *cursor, unsigned char *arenaб, int *num);

void	op_live(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_LIVE\n");
}

void	op_ld(t_cursor *cursor, unsigned char *arena, int *num);

void	op_add(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_ADD\n");
}

void	op_sub(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_SUB\n");
}

void	op_and(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_AND\n");
}

void	op_or(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_OR\n");
}

void	op_xor(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_XOR");
}

void	op_zjmp(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_ZJMP\n");
}

void	op_ldi(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_LDI\n");
}

void	op_sti(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_STI\n");
}

void	op_fork(t_cursor *cursor, unsigned char *arena, int *num);


void	op_lld(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_LLD\n");
}

void	op_lldi(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_LLDI\n");
}

void	op_lfork(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_LFORK\n");
}

void	op_aff(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_AFF\n");
}

void	init_operations(t_vm *vm)
{
	vm->do_oper[0] = op_live;
	vm->do_oper[1] = op_ld;
	vm->do_oper[2] = op_st;
	vm->do_oper[3] = op_add;
	vm->do_oper[4] = op_sub;
	vm->do_oper[5] = op_and;
	vm->do_oper[6] = op_or;
	vm->do_oper[7] = op_xor;
	vm->do_oper[8] = op_zjmp;
	vm->do_oper[9] = op_ldi;
	vm->do_oper[10] = op_sti;
	vm->do_oper[11] = op_fork;
	vm->do_oper[12] = op_lld;
	vm->do_oper[13] = op_lldi;
	vm->do_oper[14] = op_lfork;
	vm->do_oper[15] = op_aff;
}

void	set_to_arena(unsigned char *arena, int addr, int arg)
{
	*(arena + ADDR(addr)) = (arg & 0xff000000) >> 24;
	*(arena + ADDR(addr + 1)) = (arg & 0x00ff0000) >> 16;
	*(arena + ADDR(addr + 2)) = (arg & 0x0000ff00) >> 8;
	*(arena + ADDR(addr + 3)) = (arg & 0x000000ff);

}

void	op_st(t_cursor *cursor, unsigned char *arena, int *num)
{
	int		addr;
	int		arg[2];

	ft_printf("{blue}OP_ST\n");
	// ft_printf();
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
		arg[1] = bin2int(arena + cursor->cur_position + 3, IND_SIZE);
		addr = cursor->cur_position + (arg[1] % IDX_MOD);
		ft_printf("{red}arg[1] = %d\n", arg[1] % IDX_MOD);
		set_to_arena(arena, addr, cursor->r[arg[0] - 1]);
		print_arena_2(arena, addr, addr + 4);
	}
	else
		ft_printf("NOPEEPFDFSG\n");
}

void	op_ld(t_cursor *cursor, unsigned char *arena, int *num)
{
	int value;
	int	arg2;

	ft_printf("{blue}OP_LD\n");	
	// print_registers(cursor->r);
	if (IS_DIR(cursor->arg_type[0]))
	{
		arg2 = *(arena + ADDR(cursor->cur_position + 2 + DIR_SIZE));
		value = bin2int(arena + ADDR(cursor->cur_position + 2), DIR_SIZE);
		cursor->r[arg2 - 1] = value;
		cursor->carry = !value ? 1 : 0;
	}
	else if (IS_IND(cursor->arg_type[0]))
	{
		arg2 = *(arena + cursor->cur_position + 2 + IND_SIZE);
		value = cursor->cur_position + (bin2int(arena + cursor->cur_position + 2, IND_SIZE) % IDX_MOD);
		cursor->r[arg2 - 1] = bin2int(arena + value, 4);
	}
	else
		ft_printf("NONONONONONONON\n");
	// ft_printf("CARRY: %d\n", cursor->carry);
	// print_registers(cursor->r);
}
