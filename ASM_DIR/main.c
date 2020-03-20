/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 18:33:29 by ydavis            #+#    #+#             */
/*   Updated: 2020/03/01 17:44:21 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av)
{
	t_core	*core;

	core = init_core();
	check_input(core, ac, av);
	bufftostr(core);
	parser(core);
	encoder(core);
	free_core(&core);
	return (0);
}
