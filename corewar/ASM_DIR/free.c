/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 03:42:12 by ydavis            #+#    #+#             */
/*   Updated: 2020/03/01 17:02:26 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_strings(t_core *core)
{
	t_string	*str;

	if (!core->strs)
		return ;
	while (core->strs)
	{
		str = core->strs->next;
		if (core->strs->string)
			free(core->strs->string);
		if (core->strs)
			free(core->strs);
		core->strs = str;
	}
}

void	free_labels(t_core *core)
{
	t_label	*label;
	t_label	*tmp;

	label = core->labels;
	while (label)
	{
		tmp = label->next;
		if (label->name)
			free(label->name);
		if (label)
			free(label);
		label = tmp;
	}
}

void	free_tokens(t_core *core)
{
	t_token	*token;
	t_token	*tmp;
	int		i;

	token = core->tokens;
	while (token)
	{
		tmp = token->next;
		if (token->remain)
			free(token->remain);
		i = 0;
		while (i < token->op.argc)
		{
			if (!token->args)
				break ;
			if (token->args[i].str)
				free(token->args[i].str);
			i++;
		}
		if (token->args)
			free(token->args);
		if (token)
			free(token);
		token = tmp;
	}
}

void	free_core(t_core **core)
{
	if ((*core)->buff)
		free((*core)->buff);
	if ((*core)->file)
		free((*core)->file);
	if ((*core)->name)
		free((*core)->name);
	if ((*core)->comment)
		free((*core)->comment);
	if ((*core)->out)
		free((*core)->out);
	free_strings(*core);
	free_labels(*core);
	free_tokens(*core);
	if (*core)
		free(*core);
}
