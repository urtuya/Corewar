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

typedef struct	s_vm
{
	int			players_num;
	t_champ		*champ;
}				t_vm;

// typedef struct s_list
#endif


//------------------main.c

void	usage(void);
void	error(char *format, char *str);
// int		check_extention(char *file);
void	malloc_err(void *addr, char *func);

//------------------init.c
t_vm	*init_vm(void);
void	add_champ(t_champ **champ_list, t_champ *champ_to_add);
void	init_champs(int argc, char **argv, t_vm *vm);

//------------------validation.c
void	check_valid(char *file, t_champ *champ);