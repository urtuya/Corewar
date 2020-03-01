/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:36:56 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/01 03:30:52 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	error(t_core *core, char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	free_core(&core);
	exit(1);
}

void	usage(t_core *core)
{
	ft_putendl_fd("Usage: ./asm <path/to/file.s>", STDERR_FILENO);
	free_core(&core);
	exit(1);
}

void	parse_error(t_core *core, char *msg, t_string *str)
{
	ft_putnbr_fd(str->id, STDERR_FILENO);
	ft_putstr_fd(" String:\n", STDERR_FILENO);
	ft_putendl_fd(str->string, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_core(&core);
	exit(1);
}
