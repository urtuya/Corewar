/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 01:26:08 by ydavis            #+#    #+#             */
/*   Updated: 2020/03/01 19:29:06 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	name_comment(t_core *core, char *string)
{
	char	*loc;

	if (!string)
		return ;
	if (ft_strstr(string, NAME_CMD_STRING) == string)
	{
		if (core->name)
			error(core, "Double name");
		if (!(loc = ft_strchr(string, '\"')))
			error(core, "Error with name");
		core->name = get_string(core, loc + 1, PROG_NAME_LENGTH);
	}
	else if (ft_strstr(string, COMMENT_CMD_STRING) == string)
	{
		if (core->comment)
			error(core, "Double comment");
		if (!(loc = ft_strchr(string, '\"')))
			error(core, "Error with comment");
		core->comment = get_string(core, loc + 1, COMMENT_LENGTH);
	}
	else
		error(core, "No name or comment");
}

int		parse_label(t_core *core, t_string *str)
{
	int		i;

	i = 0;
	while (str->string[i])
	{
		if (str->string[i] == DIRECT_CHAR || str->string[i] == '-')
			return (0);
		if (str->string[i] == LABEL_CHAR || ft_isspace(str->string[i]))
			break ;
		i++;
	}
	if (!str->string[i])
		parse_error(core, "Unexpected end of line", str);
	if (str->string[i] == LABEL_CHAR)
	{
		make_label(core, str, i++);
		core->is_label++;
		while (str->string[i] && ft_isspace(str->string[i]))
			i++;
	}
	else
		i = 0;
	return (i);
}

void	parse_next(t_core *core, t_token *token, char *string)
{
	char	**split;

	check_malloc(split = ft_strsplit(string, SEPARATOR_CHAR));
	if (check_split(core, split, token->op.argc, string))
		parse_error(core, "Invalid number of arguments", token->str);
	token->size = 1 + token->op.argcode;
	check_malloc(token->args =
			(t_args*)malloc(sizeof(t_args) * token->op.argc));
	if (token->op.argc >= 1)
		check_args(core, split, token, 0);
	if (token->op.argc >= 2)
		check_args(core, split, token, 1);
	if (token->op.argc >= 3)
		check_args(core, split, token, 2);
	token->remain = string;
	split_free(&split);
}

void	parse_token(t_core *core, t_string *str, int flag)
{
	int		i;
	int		j;
	char	*tmp;
	t_token	*token;

	i = parse_label(core, str);
	j = i;
	while (str->string[i])
	{
		if (str->string[i] == LABEL_CHAR)
			parse_error(core, "Double label error", str);
		if (ft_isspace(str->string[i]) || str->string[i] == DIRECT_CHAR ||
				str->string[i] == '-')
			break ;
		flag = 1;
		i++;
	}
	if (!str->string[i] && !flag)
		return ;
	check_malloc(tmp = ft_strsub(str->string, j, i - j));
	token = create_token(core, tmp, str);
	parse_next(core, token, crop_string(core, str->string, i));
	token->pos = core->size;
	core->size += token->size;
	free(tmp);
}

void	parser(t_core *core)
{
	t_string	*str;
	int			i;

	str = core->strs;
	i = 0;
	while (str)
	{
		if (i < 2)
			name_comment(core, str->string);
		else
			parse_token(core, str, 0);
		str = str->next;
		if (!str)
			error(core, "No newline at the end of file");
		else if (!str->string)
			return ;
		i++;
	}
}
