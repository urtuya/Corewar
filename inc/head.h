#ifndef HEAD_H
# define HEAD_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "op.h"
# include "../libft/inc/libft.h"

# define MAGIC_HEADER_SIZE 4
# define NULL_SIZE 4
# define EXEC_CODE_SIZE 4

typedef struct	s_champ
{
	size_t			id;
	t_header		header;
	size_t			start_from;
	unsigned char	*exec_code;
	struct s_champ	*next;
}				t_champ;

typedef struct	s_cursor
{
	size_t			id;
	int				carry;
	int				op_code;
	int				last_live_cycle_nbr;
	int				cycles_before_op;
	size_t			cur_position;
	int				arg_type[3];
	int				bytes_to_next_op;
	int				r[16];
	struct s_cursor *prev;
	struct s_cursor *next;
}				t_cursor;

typedef struct	s_fl
{
	int	num;
	int	dump;
	int	d;
	int	live;
	int aff;
}				t_fl;

typedef struct	s_op
{
	int		type;
	int		arg_num;
	int		arg[3];
	int		code;
	int		cycles_to_exec;
	int		code_type_args;
	int		size_of_t_dir;
}				t_op;

typedef struct	s_vm
{
	int				players_num;
	t_champ			*champ;
	unsigned char	arena[MEM_SIZE];
	t_fl			flag;
	size_t			num_of_cursors;
	t_cursor		*cursor;
	int				last_live;
	int				num_of_cycles;
	int				nbr_live;
	int				cycles_to_die;
	int				cycles_before_check;
	int				checks;
	void			(*do_oper[16])(t_cursor*, struct s_vm*);
}				t_vm;

//------------------main.c
void			free_all(t_vm *vm);

//------------------init.c
void			init_operations(t_vm *vm);
void			init_cursors(t_vm *vm, t_cursor *new_cur, t_cursor *old,
																int addr);
t_cursor		*init_first_cursors(t_vm *vm);
t_cursor		*create_cursor(t_cursor **cursor);

//------------------velues_calculation.c
int				ft_addr(int value);
int				reverse_negative(int negative, int size);
int				bin2int(unsigned char *buf, int size);
void			bin2str(int fd, char *buf, int len);
void			set_to_arena(unsigned char *arena, int addr, int arg);

//------------------validation.c
void			check_valid(char *file, t_champ *champ);

//------------------init_main_struct.c
void			init_arena(t_vm *vm);
t_vm			*init_vm(void);
void			init_champs(t_vm *vm, char *file, int id, int flag);
//------------------start.c
void			in_cycle(t_vm *vm);

//------------------check.c
void			remove_dead_cursors(t_vm *vm, t_cursor *cursor);
void			inspection(t_vm *vm, t_cursor *cursor);
int				size_arg_type(int arg, int op_code);
int				check_arg_type(t_cursor *cursor);
int				check_registers(t_cursor *cursor, unsigned char *arena);

//------------------print_info.c TEST
void			print_info(t_champ *champ);
void			print_arena(unsigned char *arena, t_champ *champ,
															int next_byte);
void			print_arena_2(unsigned char *arena, int addr, int len);
void			print_list_of_cursors(t_cursor *cursor);
void			print_registers(int *registers);

//------------------print.c
void			usage(void);
void			error(char *format, void *str);
void			malloc_err(void *addr, char *func);
void			introduce(t_champ *champ);
void			print_dump(t_fl flag, unsigned char *arena);
void			print_winner(t_vm *vm);

//------------------parse_args.c
void			parsing_args(t_vm *vm, int *ac, char ***av);

//------------------operations.c
void			op_live(t_cursor *cursor, t_vm *vm);
void			op_add(t_cursor *cursor, t_vm *vm);
void			op_sub(t_cursor *cursor, t_vm *vm);
void			op_and(t_cursor *cursor, t_vm *vm);
void			op_or(t_cursor *cursor, t_vm *vm);
void			op_xor(t_cursor *cursor, t_vm *vm);
void			op_zjmp(t_cursor *cursor, t_vm *vm);
void			op_ldi(t_cursor *cursor, t_vm *vm);
void			op_sti(t_cursor *cursor, t_vm *vm);
void			op_fork(t_cursor *cursor, t_vm *vm);
void			op_lfork(t_cursor *cursor, t_vm *vm);
void			op_lld(t_cursor *cursor, t_vm *vm);
void			op_lldi(t_cursor *cursor, t_vm *vm);
void			op_aff(t_cursor *cursor, t_vm *vm);
void			op_st(t_cursor *cursor, t_vm *vm);
void			op_ld(t_cursor *cursor, t_vm *vm);
int				get_args(t_cursor *cursor, unsigned char *arena, int i, int *move);

//------------------op.c
t_op			*t_op_tab();

#endif
