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

# define LIVE 0x01
# define LD 0x02
# define ST 0x03
# define ADD 0x04
# define SUB 0x05
# define AND 0x06
# define OR 0x07
# define XOR 0x08
# define ZJMP 0x09
# define LDI 0x0a
# define STI 0x0b
# define FORK 0x0c
# define LLD 0x0d
# define LLDI 0x0e
# define LFORK 0x0f
# define AFF 0x10

# define IS_REG(x) (REG_CODE == x ? 1 : 0)
# define IS_IND(x) (IND_CODE == x ? 1 : 0)
# define IS_DIR(x) (DIR_CODE == x ? 1 : 0)
# define ADDR(x) (x % MEM_SIZE)

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

	char			*CHAMP_NAME;
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

typedef struct	s_arena
{
	size_t			addr;
	int				champ_id;
	char			*champ_name;
	unsigned char	*code;
}				t_arena;

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

typedef void	(*func);

typedef struct	s_vm
{
	int				players_num;
	t_champ			*champ;
	unsigned char	arena[MEM_SIZE];
	t_fl			flag;
	int				was_inspected;
	int				next_byte;
	size_t			num_of_cursors;
	t_cursor		*cursor;
	int				last_live;
	int				num_of_cycles; //num of cycles
	int				nbr_live;
	int				cycles_to_die;
	int				checks; // num of checks/inspection()
	void			(*do_oper[16])(t_cursor*, struct s_vm*);//unsigned char*, int*);
}				t_vm;

t_op	op_tab[17];

// typedef struct s_list

//------------------main.c

void	usage(void);
void	error(char *format, void *str);
// int		check_extention(char *file);
void	malloc_err(void *addr, char *func);

//------------------init.c
t_vm	*init_vm(void);
void	add_champ(t_champ **champ_list, t_champ *champ_to_add);
void	init_champs(int argc, char **argv, t_vm *vm);
void		init_cursors(t_vm *vm, t_cursor *new_cur, t_cursor *old, int addr);
t_cursor	*init_first_cursors(t_vm *vm);

//------------------validation.c
void	check_valid(char *file, t_champ *champ);
int		bin2int(unsigned char *buf, int size);

//------------------arena.c
void	init_arena(t_vm *vm);

//------------------print_info.c
void	print_info(t_vm *vm);
void	print_arena(unsigned char *arena, t_champ *champ, int next_byte);
void	print_list_of_cursors(t_cursor *cursor);


//------------------start.c
void	start(t_vm *vm);


//operations.c


#endif
