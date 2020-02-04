#include "head.h"

void	op_st(t_cursor *cursor, unsigned char *arena);

void	op_live(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_LIVE\n");
}

void	op_ld(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_LD\n");	
}

void	op_add(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_ADD\n");
}

void	op_sub(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_SUB\n");
}

void	op_and(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_AND\n");
}

void	op_or(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_OR\n");
}

void	op_xor(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_XOR");
}

void	op_zjmp(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_ZJMP\n");
}

void	op_ldi(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_LDI\n");
}

void	op_sti(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_STI\n");
}

void	op_fork(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_FORK\n");
}

void	op_lld(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_LLD\n");
}

void	op_lldi(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_LLDI\n");
}

void	op_lfork(t_cursor *cursor, unsigned char *arena)
{
	ft_printf("{blue}OP_LFORK\n");
}

void	op_aff(t_cursor *cursor, unsigned char *arena)
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
