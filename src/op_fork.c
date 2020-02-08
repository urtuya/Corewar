#include "head.h"

void	op_fork(t_cursor *cursor, t_vm *vm,/*unsigned char *arena,*/ int *num)
{
	t_cursor *add;
	int	addr;
	unsigned char	*arena;

	arena = vm->arena;
	ft_printf("{blue}OP_FORK\n");
	addr = bin2int(arena + ADDR(cursor->cur_position + 1), 2) % IDX_MOD; // size of T_DIR = 2
	malloc_err((add = (t_cursor*)malloc(sizeof(t_cursor))), "op_fork");
	cursor->head->prev = add;
	add->next = cursor->head;
	cursor->head = add;
	add->id = ++(*num);
	ft_memcpy(add->r, cursor->r, sizeof(cursor->r));
	add->carry = cursor->carry;
	add->last_live_cycle_nbr = cursor->last_live_cycle_nbr;
	add->cur_position = addr;
	ft_printf("new curs ID: %d\n", add->id);
}

void	op_lfork(t_cursor *cursor, t_vm *vm, int *num)
{
	t_cursor *add;
	int	addr;
	unsigned char	*arena;

	arena = vm->arena;
	ft_printf("{blue}OP_FORK\n");
	addr = bin2int(arena + ADDR(cursor->cur_position + 1), DIR_SIZE); // size of T_DIR = 2
	malloc_err((add = (t_cursor*)malloc(sizeof(t_cursor))), "op_fork");
	cursor->head->prev = add;
	add->next = cursor->head;
	cursor->head = add;
	add->id = ++(*num);
	ft_memcpy(add->r, cursor->r, sizeof(cursor->r));
	add->carry = cursor->carry;
	add->last_live_cycle_nbr = cursor->last_live_cycle_nbr;
	add->cur_position = addr;
	ft_printf("new curs ID: %d\n", add->id);
}
