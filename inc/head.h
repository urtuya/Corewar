#ifndef HEAD_H
# define HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "op.h"
#include "../libft/inc/libft.h"

# define MAGIC_HEADER_SIZE 4
# define NULL_SIZE 4
# define EXEC_CODE_SIZE 4

typedef struct	s_champ
{
	int				id;
	t_header		header;
	unsigned char	*exec_code;
	struct s_champ	*next;
}				t_champ;

typedef struct	s_cursor
{
	int				id;
	int 			carry;
	int				op_code;
	int				last_live_cycle_nbr;
	int				cycle_num; // num of cycles until op
	size_t			cur_addr; // addr of current cursor
	int				bytes_to_get;
	int				r[16];

	char			*CHAMP_NAME;

	struct s_cursor *next;
}				t_cursor;

typedef struct	s_fl
{
	int	dump;
	int	n;
}				t_fl;

typedef struct	s_vm
{
	int				players_num;
	t_champ			*champ;
	t_champ			champs[4];
	unsigned char	arena[MEM_SIZE];
	t_fl			flag;

	t_cursor		*cursor;
	int				last_live;
	int				cycles;
	int				nbr_live;
	int				cycles_to_die;
	int				max_checks;
	t_champ			*champ_head;
}				t_vm;



// typedef struct s_list
#endif


//------------------main.c

void	usage(void);
void	error(char *format, void *str);
// int		check_extention(char *file);
void	malloc_err(void *addr, char *func);

//------------------init.c
t_vm	*init_vm(void);
void	add_champ(t_champ **champ_list, t_champ *champ_to_add);
void	init_champs(int argc, char **argv, t_vm *vm);

//------------------validation.c
void	check_valid(char *file, t_champ *champ);
int		bin2int(unsigned char *buf, int size);

//------------------arena.c
void	init_arena(t_vm *vm);