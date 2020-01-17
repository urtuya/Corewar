#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	t_champ kek;

	strcpy(kek.lol.prog_name, "lolkekcheburek");
	printf("pro = %s\n", kek.lol.prog_name);

	return (0);
}