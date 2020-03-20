/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vellery- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 21:04:02 by vellery-          #+#    #+#             */
/*   Updated: 2019/10/10 21:04:10 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	save_in(char **stack, int fd, char **line)
{
	int i;

	i = 0;
	while (stack[fd][i] && stack[fd][i] != '\n')
		i++;
	if (!(*line = ft_strsub(stack[fd], 0, i)))
		return (-1);
	return (i);
}

static char	*f_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (char)c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char*)s);
}

static int	go_to_func(char **stack, int fd, char **line)
{
	char	*forline;
	char	*point;
	int		len;

	if (f_strchr(stack[fd], '\n') != NULL)
	{
		len = save_in(stack, fd, line) + 1;
		if (!(forline = ft_strsub(stack[fd], len, ft_strlen(stack[fd]))))
			return (-1);
		ft_strdel(&stack[fd]);
		if (!(stack[fd] = ft_strdup(forline)))
			return (-1);
		ft_strdel(&forline);
	}
	else
	{
		point = stack[fd];
		if (!(*line = ft_strsub(stack[fd], 0, ft_strlen(stack[fd]))))
			return (-1);
		stack[fd] = &stack[fd][ft_strlen(stack[fd])];
		free(point);
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char	*stack[255];
	char		buf[BUFF_SIZE + 1];
	char		*forline;
	int			size;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((size = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[size] = '\0';
		if (stack[fd] == NULL)
			stack[fd] = ft_strnew(0);
		forline = ft_strjoin(stack[fd], buf);
		ft_strdel(&stack[fd]);
		stack[fd] = ft_strdup(forline);
		ft_strdel(&forline);
		if ((forline = f_strchr(stack[fd], '\n')) != NULL)
			break ;
	}
	if (size < 0)
		return (-1);
	if (size == 0 && (stack[fd][0] == '\0' || stack[fd] == NULL))
		return (0);
	return (go_to_func(stack, fd, line));
}
