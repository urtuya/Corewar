#include "head.h"

t_cursor	*init_cursors(t_vm *vm);








void	print_list_of_cursors(t_cursor *cursor)
{
	while (cursor)
	{
		ft_printf("ID: %d\n", cursor->id);
		ft_printf("{red}CHAMP: %s\n", cursor->CHAMP_NAME);
		if (cursor->next)
		{
			ft_printf("|\n");
			ft_printf("V\n");
		}
		cursor = cursor->next;
	}
}


void	start(t_vm *vm)
{
	init_cursors(vm);

	print_list_of_cursors(vm->cursor);

}



// //-----------------------ARRAY OF CHAMPS
// void	init_champs(int argc, char **argv, t_vm *vm)
// {
// 	int i;

// 	i = 0;
// 	while (i < argc)
// 	{
// 		check_valid(argv[i], &vm->champs[i]);
// 		vm->players_num++;
// 		i++;
// 	}	
// }


