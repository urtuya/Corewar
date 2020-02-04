#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limits.h"

typedef struct					s_header
{
	unsigned int		magic;
	char				prog_name[129];
	unsigned int		prog_size;
	char				comment[2049];
}								t_lol;

typedef struct s_champ
{
	int id;
	t_lol lol;
}				t_champ;


int main()
{
	int a = -1;

	printf("%#x\n", (a & 0xff000000));
	return (0); 
}