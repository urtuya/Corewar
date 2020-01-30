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
	int code = 106;

	int q = 0b10;
	int p = 0b11;
	printf("%d\n", q & p);
	return (0);
}