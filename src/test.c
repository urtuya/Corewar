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
	int array[16] = {0, 1, 2, 3, 5};
	int copy[16] = {0};
	int i;

	i = 0;
	while (i < 16)
	{
		printf("[%d]: %d  ", i + 1, copy[i]);
		i++;
	}
	printf("\n");
	memcpy(copy, array, sizeof(copy));
	i = 0;
	while (i < 16)
	{
		printf("[%d]: %d  ", i + 1, copy[i]);
		i++;
	}

	// printf("%#x\n", (a & 0xff000000));
	return (0); 
}