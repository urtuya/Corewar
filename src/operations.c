#include "head.h"

void	set_to_arena(unsigned char *arena, int addr, int arg)
{
	*(arena + ft_addr(addr)) = (arg & 0xff000000) >> 24;
	*(arena + ft_addr(addr + 1)) = (arg & 0x00ff0000) >> 16;
	*(arena + ft_addr(addr + 2)) = (arg & 0x0000ff00) >> 8;
	*(arena + ft_addr(addr + 3)) = (arg & 0x000000ff);

}

void	op_live(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int	arg;
	int	move;

	cursor->last_live_cycle_nbr = vm->num_of_cycles;
	// printf("CURSOR %ld SAID LIVE\n", cursor->id);
	vm->nbr_live++;
	arena = vm->arena;
	move = 1;
	arg = -get_args(cursor, arena, 0, &move);
	if (arg == cursor->r[0])//arg > 0 && arg <= vm->players_num)
	{
		// printf("PLAYER %d IS ALIVE!\n", -arg);
		vm->last_live = -arg;
	}
	ft_printf("{blue}OP_LIVE %d\n", -arg);
}

void	op_add(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int	sum;
	int	args[3];

	arena = vm->arena;
	args[0] = *(arena + ft_addr(cursor->cur_position + 2)) - 1;
	args[1] = *(arena + ft_addr(cursor->cur_position + 3)) - 1;
	args[2] = *(arena + ft_addr(cursor->cur_position + 4)) - 1;
	sum = cursor->r[args[0]] + cursor->r[args[1]];
	cursor->r[args[2]] = sum;
	if (!sum)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	// printf("WRITING R[%d] + R[%d] = R[%d]\n%d + %d = %d\n", args[0], args[1], args[2], cursor->r[args[0]], cursor->r[args[1]], cursor->r[args[2]]);
	ft_printf("{blue}OP_ADD\n%d %d\n", cursor->carry, sum);
}

void	op_sub(t_cursor *cursor, t_vm *vm)
{
	int	sum;
	int	args[3];
	unsigned char	*arena;

	arena = vm->arena;
	args[0] = *(arena + ft_addr(cursor->cur_position + 2)) - 1;
	args[1] = *(arena + ft_addr(cursor->cur_position + 3)) - 1;
	args[2] = *(arena + ft_addr(cursor->cur_position + 4)) - 1;
	sum = cursor->r[args[0]] - cursor->r[args[1]];
	cursor->r[args[2]] = sum;
	if (!sum)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	
	ft_printf("{blue}OP_SUB carry = %d\n", cursor->carry);
}

int	get_args(t_cursor *cursor, unsigned char *arena, int i, int *move)
{
	// USE IT TO GET ARGS (EXAMPLE BELOW IN OP_AND FUNCTION AND OTHERS)
	int	ret;
	int	size;
	int	tmp; // DELETE ME!!!!!!1
	
	// printf("GET ARGS!\n");
	if (IS_REG(cursor->arg_type[i]))
	{
		// printf("ITS REG!\n");
		tmp = *(arena + ft_addr(cursor->cur_position + *move)) - 1;
		// printf("TAKING R[%d] == %d\n", tmp, cursor->r[tmp]);
		ret = cursor->r[*(arena + ft_addr(cursor->cur_position + *move)) - 1];
		// ret = cursor->r[*(arena + ft_addr(cursor->cur_position + *move))];
		*move += 1;
	}
	if (IS_DIR(cursor->arg_type[i]))
	{
		size = op_tab[cursor->op_code].size_of_t_dir ? 2 : 4;
		// printf("ITS DIR!\n");
		tmp = ft_addr(cursor->cur_position + *move);
		// printf("TAKING ARENA[%d] == %d\n", tmp, bin2int(arena + tmp, size));
		ret = bin2int(arena + ft_addr(cursor->cur_position + *move), size);
		*move += size;
	}
	if (IS_IND(cursor->arg_type[i]))
	{
		// printf("ITS IND!\n");
		/*
		ret = *(arena + ft_addr(cursor->cur_position + *move));
		ret = *(arena + ft_addr(cursor->cur_position + (ret % IDX_MOD)));
		*/
		ret = bin2int(arena + ft_addr(cursor->cur_position + *move), 2);
		ret = bin2int(arena + ft_addr(cursor->cur_position + (ret % IDX_MOD)), 2);
		*move += 2;
	}
	return (ret);
}

void	op_and(t_cursor *cursor, t_vm *vm)
{
	int	sum;
	int	to;
	int	args[2];
	int	move;
	unsigned char	*arena;

	arena = vm->arena;

	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ft_addr(cursor->cur_position + move)) - 1;
	//  printf("TO %d\nMOVE %d\n", to, move);
	sum = args[0] & args[1];
	cursor->r[to] = sum;
	if (!sum)
		cursor->carry = 1;
	else
		cursor->carry = 0;
			ft_printf("{blue}OP_AND\n");
	 ft_printf("   FIRST %d SECOND %d  SUM %d CARRY %d\n", args[0], args[1], sum, cursor->carry);
	//  exit(0);

}

void	op_or(t_cursor *cursor, t_vm *vm)
{
	int	sum;
	int	to;
	int	args[2];
	int	move;
	unsigned char	*arena;

	arena = vm->arena;

	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ft_addr(cursor->cur_position + move)) - 1;
//	printf("TO %d\nMOVE %d\n", to, move);
	sum = args[0] | args[1];
	cursor->r[to] = sum;
	if (!sum)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	ft_printf("{blue}OP_OR   ");
	ft_printf("FIRST %d SECOND %d   SUM %d   CARRY%d\n", args[0], args[1], sum, cursor->carry);
	
}

void	op_xor(t_cursor *cursor, t_vm *vm)
{
	int	sum;
	int	to;
	int	args[2];
	int	move;
	unsigned char	*arena;

	arena = vm->arena;

	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ft_addr(cursor->cur_position + move)) - 1;
	// printf("TO %d\nMOVE %d\n", to, move);
	sum = args[0] ^ args[1];
	cursor->r[to] = sum;
	if (!sum)
		cursor->carry = 1;
	else
		cursor->carry = 0;
	ft_printf("{blue}OP_XOR   ");
	ft_printf("FIRST %d SECOND %d   SUM %d CARRY%d\n", args[0], args[1], sum, cursor->carry);
	
}

void	op_zjmp(t_cursor *cursor, t_vm *vm)
{
	int	res;
	int	move;
	unsigned char	*arena;

	ft_printf("{blue}OP_ZJMP");
	arena = vm->arena;
	move = 1;
	res = get_args(cursor, arena, 0, &move);
	if (!cursor->carry)
	{
		ft_printf("NO TO %d\n", ft_addr(res % IDX_MOD));
		return ;
	}
	// ft_printf("MOVING FROM %d", cursor->cur_position);
	cursor->cur_position = ft_addr(cursor->cur_position + res % IDX_MOD);
	cursor->bytes_to_next_op = 0;
		ft_printf(" TO %d\n", ft_addr(res % IDX_MOD));
	// ft_printf("\n");

}

void	op_ldi(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int	move;
	int	args[2];
	int	to;

	arena = vm->arena;
	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ft_addr(cursor->cur_position + move)) - 1;
	cursor->r[to] = bin2int(arena + ft_addr(cursor->cur_position + (args[0] + args[1]) % IDX_MOD), REG_SIZE);
		ft_printf("{blue}OP_LDI");
	ft_printf("    WRITING %d TO R[%d] FROM %d!\n", cursor->r[to], to, cursor->cur_position + (args[0] + args[1]) % IDX_MOD);

}

void	op_sti(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int	args[3];
	int	move;
	int	addr;

	// printf("cur_pos = %d\n", cursor->cur_position);
	arena = vm->arena;
	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	printf("arg[0] = %d\n", args[0]);
	args[1] = get_args(cursor, arena, 1, &move);
	args[2] = get_args(cursor, arena, 2, &move);
	addr = ft_addr(cursor->cur_position + (args[1] + args[2]) % IDX_MOD);
	set_to_arena(arena, addr, args[0]);

	// print_arena_2(arena, addr, addr + 4);
	ft_printf("{blue}OP_STI");
		ft_printf("  r[%d]   %d  %d\n", args[0] - 1, args[1], addr);
}

void	op_fork(t_cursor *cursor, t_vm *vm)
{
	t_cursor *add;
	int	addr;
	unsigned char	*arena;

	arena = vm->arena;

	addr = bin2int(arena + ft_addr(cursor->cur_position + 1), 2); // size of T_DIR = 2
	malloc_err((add = (t_cursor*)malloc(sizeof(t_cursor))), "op_fork");
	vm->cursor->prev = add;
	add->next = vm->cursor;
	vm->cursor = add;
	add->prev = NULL;
	add->id = ++(vm->num_of_cursors);
	ft_memcpy(add->r, cursor->r, sizeof(cursor->r));
	add->carry = cursor->carry;
	add->last_live_cycle_nbr = cursor->last_live_cycle_nbr;
	add->cur_position = ft_addr((addr % IDX_MOD) + cursor->cur_position);
	add->parent = cursor;
	add->op_code = 0;
	add->cycles_before_op = 0;
	add->bytes_to_next_op = 0;
	// add->CHAMP_NAME = ft_strdup(cursor->CHAMP_NAME);
	// ft_printf("new curs ID: %d\n", add->id);
	vm->are_alive ++;
	// if (add->id == 28)
	// {
	// 	ft_printf("cur pos pls = %d\n", add->cur_position);
	// 	exit(0);
	// }
		ft_printf("{blue}OP_FORK\n");
}

void	op_lfork(t_cursor *cursor, t_vm *vm)
{
	t_cursor *add;
	int	addr;
	unsigned char	*arena;

	arena = vm->arena;

	addr = bin2int(arena + ft_addr(cursor->cur_position + 1), DIR_SIZE); // size of T_DIR = 2
	malloc_err((add = (t_cursor*)malloc(sizeof(t_cursor))), "op_lfork");
	vm->cursor->prev = add;
	add->next = vm->cursor;
	vm->cursor = add;
	add->prev = NULL;
	add->id = ++(vm->num_of_cursors);
	ft_memcpy(add->r, cursor->r, sizeof(cursor->r));
	add->carry = cursor->carry;
	add->last_live_cycle_nbr = cursor->last_live_cycle_nbr;
	add->cur_position = (addr + cursor->cur_position) % MEM_SIZE;
	add->parent = cursor;
	add->op_code = 0;
	add->cycles_before_op = 0;
	add->bytes_to_next_op = 0;
	vm->are_alive ++;
	// ft_printf("new curs ID: %d\n", add->id);
		ft_printf("{blue}OP_LFORK\n");
}

void	op_lld(t_cursor *cursor, t_vm *vm)
{
	int value;
	int	arg2;
	int	move;
	unsigned char	*arena;

	ft_printf("{blue}OP_LLD\n");
	arena = vm->arena;
	if (IS_DIR(cursor->arg_type[0]))
	{
		arg2 = *(arena + ft_addr(cursor->cur_position + 2 + DIR_SIZE));
		value = bin2int(arena + ft_addr(cursor->cur_position + 2), DIR_SIZE);
		cursor->r[arg2 - 1] = value;
		cursor->carry = !value ? 1 : 0;
		printf("ASSIGNING %d TO R[%d]\n", value, arg2 - 1);
	}
	else if (IS_IND(cursor->arg_type[0]))
	{
		arg2 = *(arena + ft_addr(cursor->cur_position + 2 + IND_SIZE));
		value = cursor->cur_position + (bin2int(arena + ft_addr(cursor->cur_position + 2), IND_SIZE));
		cursor->r[arg2 - 1] = bin2int(arena + ft_addr(value), 4);
		cursor->carry = !cursor->r[arg2 - 1] ? 1 : 0;
		printf("ASSIGNING %d TO R[%d]\n", bin2int(arena + ft_addr(value), 4), arg2 - 1);
	}
	else
		ft_printf("NONONONONONONON\n");

}

void	op_lldi(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int	move;
	int	args[2];
	int	to;

	ft_printf("{blue}OP_LLDI\n");
	arena = vm->arena;
	move = 2;
	args[0] = get_args(cursor, arena, 0, &move);
	args[1] = get_args(cursor, arena, 1, &move);
	to = *(arena + ft_addr(cursor->cur_position + move)) - 1;
	if (to > REG_NUMBER || to <= 0)
	{
		printf("WRONG REG NUMBER: %d\n", to);
		return ; 
	}
	cursor->r[to] = bin2int(arena + ft_addr(cursor->cur_position + args[0] + args[1]), REG_SIZE);
	ft_printf("WRITING %d TO R[%d] FROM %d!\n", cursor->r[to], to, cursor->cur_position + args[0] + args[1]);
	if (cursor->r[to])
		cursor->carry = 0;
	else
		cursor->carry = 1;

}

void	op_aff(t_cursor *cursor, t_vm *vm)
{
	unsigned char	*arena;
	int	move;
	int	arg;

	arena = vm->arena;
	move = 2;
	arg = get_args(cursor, arena, 0, &move);
	ft_putchar_fd((char)arg, STDOUT_FILENO);
	ft_printf("{blue}OP_AFF\n");
}



void	op_st(t_cursor *cursor, t_vm *vm)
{
	int		addr;
	int		arg[2];
	int		move;
	unsigned char	*arena;

	arena = vm->arena;


	// ft_printf();
	
	arg[0] = arena[ft_addr(cursor->cur_position + 2)] - 1;
	move = 3;
	if (IS_REG(cursor->arg_type[1]))
	{
		// print_registers(cursor->r);
		arg[1] = *(arena + ft_addr(cursor->cur_position + 3)) - 1;
		cursor->r[arg[1]] = cursor->r[arg[0]]; // - 1 потому что счет с нуля
		// print_registers(cursor->r);
		// ft_printf("LOL\n");
	}
	else if (IS_IND(cursor->arg_type[1]))
	{
		arg[1] = bin2int(arena + cursor->cur_position + 3, IND_SIZE);
		addr = cursor->cur_position + (arg[1] % IDX_MOD);
		// ft_printf("{red}arg[1] = %d\n", arg[1] % IDX_MOD);
		// ft_printf("WRITING TO %d\n", cursor->cur_position + (arg[1] % IDX_MOD));
		set_to_arena(arena, addr, cursor->r[arg[0]]);
		// print_arena_2(arena, addr, addr + 4);
	}
	else
		ft_printf("NOPEEPFDFSG\n");
	ft_printf("{blue}OP_ST\n");
}

void	op_ld(t_cursor *cursor, t_vm *vm)
{
	int value;
	int	arg2;
//	int	move;
	unsigned char	*arena;

	arena = vm->arena;
	// print_registers(cursor->r);

	// COMMENT FOR PREVIOUS VERSION
	/*
	move = 2;
	value = get_args(cursor, arena, 0, &move);
	arg2 = *(arena + ft_addr(cursor->cur_position + move));
	if (!(cursor->r[arg2 - 1] = value))
		cursor->carry = 1;
	else
		cursor->carry = 0;
	printf("ASSIGNING %d TO R[%d], CARRY = %d\n", value, arg2 - 1, cursor->carry);
	*/

	ft_printf("{blue}OP_LD");
	if (IS_DIR(cursor->arg_type[0]))
	{
		arg2 = *(arena + ft_addr(cursor->cur_position + 2 + DIR_SIZE));
		value = bin2int(arena + ft_addr(cursor->cur_position + 2), DIR_SIZE);
		cursor->r[arg2 - 1] = value;
		cursor->carry = !value ? 1 : 0;
		printf("  ASSIGNING %d TO R[%d]\n", value, arg2 - 1);
	}
	else if (IS_IND(cursor->arg_type[0]))
	{
		arg2 = *(arena + ft_addr(cursor->cur_position + 2 + IND_SIZE));
		value = cursor->cur_position + (bin2int(arena + cursor->cur_position + 2, IND_SIZE) % IDX_MOD);
		cursor->r[arg2 - 1] = bin2int(arena + ft_addr(value), 4);
		cursor->carry = !cursor->r[arg2 - 1] ? 1 : 0;
		printf("   ASSIGNING %d TO R[%d]\n", bin2int(arena + ft_addr(value), 4), arg2 - 1);
	}
	else
		ft_printf("NONONONONONONON\n");

	// ft_printf("CARRY: %d\n", cursor->carry);
	// print_registers(cursor->r);

}

void	init_operations(t_vm *vm)
{
	vm->do_oper[0] = op_live; // DONE (DOUBLECHECK THE INSTRUCTIONS)
	vm->do_oper[1] = op_ld; // DONE
	vm->do_oper[2] = op_st; // DONE
	vm->do_oper[3] = op_add; // DONE
	vm->do_oper[4] = op_sub; // DONE
	vm->do_oper[5] = op_and; // DONE
	vm->do_oper[6] = op_or; // DONE
	vm->do_oper[7] = op_xor; // DONE
	vm->do_oper[8] = op_zjmp; // DONE
	vm->do_oper[9] = op_ldi; // DONE (OMG IM STUPID)  sort like ok
	vm->do_oper[10] = op_sti; // DONE (OMG IM STUPID * 2)  kogda znachenie ushlo v minus, vm srabotala, no originalnaya - net
	vm->do_oper[11] = op_fork; // DONE (DOUBLECHECK) sort like ok
	vm->do_oper[12] = op_lld; // DONE (DOUBLECHECK)  
	vm->do_oper[13] = op_lldi; // DONE (DOUBLECHECK) 
	vm->do_oper[14] = op_lfork; // DONE (DOUBLECHECK) sort like ok
	vm->do_oper[15] = op_aff; // DONE
}
