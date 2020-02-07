#include "head.h"

void	op_live(t_cursor *cursor, unsigned char *arena, int *num)
{
	ft_printf("{blue}OP_LIVE\n");
}

void	op_add(t_cursor *cursor, unsigned char *arena, int *num)
{
	int	sum;
	int	args[3];

	args[0] = *(arena + ADDR(cursor->cur_position + 2));
	args[1] = *(arena + ADDR(cursor->cur_position + 3));
	args[2] = *(arena + ADDR(cursor->cur_position + 4));
	sum = cursor->r[args[0]] + cursor->r[args[1]];
	if (!(cursor->r[args[2]] = sum))
		cursor->carry = 1;
	else
		cursor->carry = 0;
	ft_printf("{blue}OP_ADD\n%d %d\n", cursor->carry, sum);
	
}

void	op_sub(t_cursor *cursor, unsigned char *arena, int *num)
{
	int	sum;
	int	args[3];

	args[0] = *(arena + ADDR(cursor->cur_position + 2));
	args[1] = *(arena + ADDR(cursor->cur_position + 3));
	args[2] = *(arena + ADDR(cursor->cur_position + 4));
	sum = cursor->r[args[0]] - cursor->r[args[1]];
	if (!(cursor->r[args[2]] = sum))
		cursor->carry = 1;
	else
		cursor->carry = 0;
	
	ft_printf("{blue}OP_SUB\n");
}

int	get_args(t_cursor *cursor, unsigned char *arena, int i, int *move)
{
	int	ret;
	// JUST TESTING
	int	size;

	if (IS_REG(cursor->arg_type[i]))
	{
		printf("ITS REG!\n");
		ret = cursor->r[*(arena + ADDR(cursor->cur_position + *move))];
		*move += 1;
	}
	if (IS_DIR(cursor->arg_type[i]))
	{
		size = op_tab[cursor->op_code].size_of_t_dir ? 2 : 4;
		printf("ITS DIR!\n");
		ret = bin2int(arena + ADDR(cursor->cur_position + *move), size);
		printf("%d %d\n", ret, DIR_SIZE);
		*move += size;
	}
	if (IS_IND(cursor->arg_type[i]))
	{
		printf("ITS IND!\n");
		ret = *(arena + ADDR(cursor->cur_position + *move));
		ret = *(arena + cursor->cur_position + (ret % IDX_MOD));
		*move += 2;
	}
	return (ret);
}

void	op_and(t_cursor *cursor, unsigned char *arena, int *num)
{
	int	sum;
	int	to;
	int	args[2];
	int	move;

	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ADDR(cursor->cur_position + move));
	// printf("TO %d\nMOVE %d\n", to, move);
	sum = args[0] & args[1];
	if (!(cursor->r[to] = sum))
		cursor->carry = 1;
	else
		cursor->carry = 0;
	// ft_printf("OP_AND\nFIRST %d SECOND %d\nSUM %d CARRY%d\n", args[0], args[1], sum, cursor->carry);
	exit(0);
}

void	op_or(t_cursor *cursor, unsigned char *arena, int *num)
{
	int	sum;
	int	to;
	int	args[2];
	int	move;

	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ADDR(cursor->cur_position + move));
//	printf("TO %d\nMOVE %d\n", to, move);
	sum = args[0] | args[1];
	if (!(cursor->r[to] = sum))
		cursor->carry = 1;
	else
		cursor->carry = 0;
//	ft_printf("OP_AND\nFIRST %d SECOND %d\nSUM %d CARRY%d\n", args[0], args[1], sum, cursor->carry);
//	ft_printf("{blue}OP_OR\n");
}

void	op_xor(t_cursor *cursor, unsigned char *arena, int *num)
{
	int	sum;
	int	to;
	int	args[2];
	int	move;

	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ADDR(cursor->cur_position + move));
	printf("TO %d\nMOVE %d\n", to, move);
	sum = args[0] ^ args[1];
	if (!(cursor->r[to] = sum))
		cursor->carry = 1;
	else
		cursor->carry = 0;
	ft_printf("OP_AND\nFIRST %d SECOND %d\nSUM %d CARRY%d\n", args[0], args[1], sum, cursor->carry);
	ft_printf("{blue}OP_XOR");
}

void	op_zjmp(t_cursor *cursor, unsigned char *arena, int *num)
{
	int	res;
	int	move;

	if (!cursor->carry)
		return ;
	move = 1;
	res = get_args(cursor, arena, 0, &move);
	printf("MOVING FROM %d", cursor->cur_position);
	cursor->cur_position = ADDR(cursor->cur_position + res) % IDX_MOD;
	cursor->bytes_to_next_op = 0;
	printf(" TO %d\n", cursor->cur_position);
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
		// NO, IT DOESNT, r[0..15], YOU DONT NEED TO DECREMENT IT BY 1!!!
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
		printf("ASSIGNING %d TO R[%d]\n", value, arg2 - 1);
	}
	else if (IS_IND(cursor->arg_type[0]))
	{
		arg2 = *(arena + cursor->cur_position + 2 + IND_SIZE);
		value = cursor->cur_position + (bin2int(arena + cursor->cur_position + 2, IND_SIZE) % IDX_MOD);
		cursor->r[arg2 - 1] = bin2int(arena + value, 4);
		cursor->carry = !cursor->r[arg2 - 1] ? 1 : 0;
		printf("ASSIGNING %d TO R[%d]\n", bin2int(arena + value, 4), arg2 - 1);
	}
	else
		ft_printf("NONONONONONONON\n");
	// ft_printf("CARRY: %d\n", cursor->carry);
	// print_registers(cursor->r);
}

void	init_operations(t_vm *vm)
{
	vm->do_oper[0] = op_live;
	vm->do_oper[1] = op_ld; // DONE
	vm->do_oper[2] = op_st; // DONE
	vm->do_oper[3] = op_add; // DONE
	vm->do_oper[4] = op_sub; // DONE
	vm->do_oper[5] = op_and; // DONE
	vm->do_oper[6] = op_or; // DONE
	vm->do_oper[7] = op_xor; // DONE
	vm->do_oper[8] = op_zjmp; // I DONT BELEIVE IT, DOUBLECHECK FOR FUCKS SAKE
	vm->do_oper[9] = op_ldi;
	vm->do_oper[10] = op_sti;
	vm->do_oper[11] = op_fork;
	vm->do_oper[12] = op_lld;
	vm->do_oper[13] = op_lldi;
	vm->do_oper[14] = op_lfork;
	vm->do_oper[15] = op_aff;
}
