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

# define IS_REG(x) (T_REG == x ? 1 : 0)
# define IS_IND(x) (T_IND == x ? 1 : 0)
# define IS_DIR(x) (T_DIR == x ? 1 : 0)

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
	int 			carry;
	int				op_code;
	int				last_live_cycle_nbr;
	int				cycles_before_op; // num of cycles until op
	size_t			cur_position; // addr of current cursor
	int				arg_type[3];
	int				bytes_to_next_op;
	int				r[16];
	struct s_cursor *prev;
	struct s_cursor *next;
}				t_cursor;

typedef struct	s_fl
{
	int	dump;	//32 octets
	int	d;		//64 octets
	int	n;
	int	aff;	//print char
}				t_fl;

typedef struct	s_op
{
	char	*name;
	int		type; //01 10 11 type of arg
	int		arg_num;
	int		arg[3];
	int		code;
	int		cycles_to_exec;
	int		code_type_args;// code of arguments types: 1 = exist, 0 - nonexist
	int		size_of_t_dir; //  0=4, 1=2
}				t_op;


typedef struct	s_vm
{
	size_t			are_alive;
	int				players_num;
	t_champ			*champ;
	unsigned char	arena[MEM_SIZE];
	t_fl			flag;
	// int				was_inspected;
	int				next_byte;
	size_t			num_of_cursors;
	t_cursor		*cursor;
	int				last_live;
	int				num_of_cycles; //num of cycles
	int				nbr_live;
	int				cycles_to_die;
	int				cycles_before_check;
	int				checks; // num of checks/inspection()
	void			(*do_oper[16])(t_cursor*, struct s_vm*);
}				t_vm;

t_op	op_tab[17];

// typedef struct s_list

//------------------main.c

//------------------init.c
t_vm		*init_vm(void);
void		add_champ(t_champ **champ_list, t_champ *champ_to_add);
void		init_champs(int argc, char **argv, t_vm *vm);
void		init_cursors(t_vm *vm, t_cursor *new_cur, t_cursor *old, int addr);
t_cursor	*init_first_cursors(t_vm *vm);

//------------------velues_calculation.c
int		ft_addr(int value);
int		reverse_negative(int negative, int size);
int		bin2int(unsigned char *buf, int size);
void	bin2str(int fd, char *buf, int len);

//------------------validation.c
void	check_valid(char *file, t_champ *champ);

//------------------arena.c
void	init_arena(t_vm *vm);

//------------------print_info.c
void	print_info(t_vm *vm);
void	print_arena(unsigned char *arena, t_champ *champ, int next_byte);
void	print_list_of_cursors(t_cursor *cursor);


//------------------start.c
void	in_cycle(t_vm *vm);

//------------------check.c
void	remove_dead_cursor(t_vm *vm, t_cursor *cursor);
void	inspection(t_vm *vm, t_cursor *cursor);
int		size_arg_type(int arg, int op_code);
int		check_arg_type(t_cursor *cursor);
int		check_registers(t_cursor *cursor, unsigned char *arena);

//------------------print_info.c TEST
void	introduce(t_champ *champ);
void	print_info(t_vm *vm);
void	print_arena(unsigned char *arena, t_champ *champ, int next_byte);
void	print_arena_2(unsigned char *arena, int addr, int len);
void	print_list_of_cursors(t_cursor *cursor);
void	print_registers(int *registers);
//------------------operations.c


#endif
