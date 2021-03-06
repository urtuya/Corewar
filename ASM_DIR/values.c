/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 02:53:49 by ydavis            #+#    #+#             */
/*   Updated: 2020/02/22 19:43:02 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	direct_value(t_core *core, t_token *token, int i)
{
	char	*tmp;
	int		j;

	check_malloc(tmp = ft_strtrim(token->args[i].str));
	j = 1;
	while (tmp[j])
	{
		if (tmp[j] == '+' || (!ft_isdigit(tmp[j]) && tmp[j] != '-'))
		{
			free(tmp);
			parse_error(core, "Illegal character in direct arg", token->str);
		}
		j++;
	}
	token->args[i].value = ft_atoi(tmp + 1);
	free(tmp);
	token->args[i].type = 2;
}

void	register_value(t_core *core, t_token *token, int i)
{
	char	*trim;
	char	*tmp;

	check_malloc(trim = ft_strtrim(token->args[i].str));
	tmp = trim + 1;
	if (!ft_isdigital(tmp) || ft_strlen(tmp) > 2)
	{
		free(trim);
		parse_error(core, "Illegal character in register arg", token->str);
	}
	token->args[i].value = ft_atoi(tmp);
	free(trim);
	token->args[i].type = 1;
}

void	indirect_value(t_core *core, t_token *token, int i)
{
	char	*tmp;
	int		j;

	check_malloc(tmp = ft_strtrim(token->args[i].str));
	j = 0;
	while (tmp[j])
	{
		if (tmp[j] == '+' || (!ft_isdigit(tmp[j]) && tmp[j] != '-'))
		{
			free(tmp);
			parse_error(core, "Illegal character in indirect arg", token->str);
		}
		j++;
	}
	token->args[i].value = ft_atoi(tmp);
	free(tmp);
}

void	direct_label(t_core *core, t_token *token, int i)
{
	t_label	*label;
	char	*tmp;

	check_malloc(tmp = ft_strtrim(token->args[i].str));
	label = core->labels;
	while (label)
	{
		if (ft_strequ(tmp + 2, label->name))
			break ;
		label = label->next;
	}
	if (!label)
	{
		free(tmp);
		parse_error(core, "No such label", token->str);
	}
	if (!label->to)
		token->args[i].value = (int)(core->size - token->pos);
	else
		token->args[i].value = (int)(label->to->pos - token->pos);
	free(tmp);
	token->args[i].type = 2;
}

void	indirect_label(t_core *core, t_token *token, int i)
{
	char	*tmp;
	t_label	*label;

	check_malloc(tmp = ft_strtrim(token->args[i].str));
	label = core->labels;
	while (label)
	{
		if (ft_strequ(tmp + 1, label->name))
			break ;
		label = label->next;
	}
	if (!label)
	{
		free(tmp);
		parse_error(core, "No such label", token->str);
	}
	if (!label->to)
		token->args[i].value = (int)(core->size - token->pos);
	else
		token->args[i].value = (int)(label->to->pos - token->pos);
	free(tmp);
	token->args[i].type = 3;
}
