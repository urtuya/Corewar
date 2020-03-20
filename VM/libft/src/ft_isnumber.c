#include "libft.h"
#include <stdio.h>

static int	clear_spaces(char *str, int *base)
{
	int i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	if (str[i] && str[i] == '0')
	{
		*base = 8;
		i++;
		if (lower_upper(str[i], 'x'))
		{
			*base = 16;
			i++;
		}
		else if (lower_upper(str[i], 'b'))
		{
			*base = 2;
			i++;
		}
	}
	else
		*base = 10;
	return (i);
}	

static int	is_hex(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
	{
		return (1);
	}
	return (0);
}

int			ft_isnumber(char *str)
{
	int i;
	int	base;

	if (!str || !*str)
		return (0);
	i = clear_spaces(str, &base);
	while (str[i])
	{
		if ((ft_isdigit(str[i]) && base == 10) ||
			((str[i] == '1' || str[i] == '0') && base == 2) ||
			(base == 16 && (is_hex(str[i]) || ft_isdigit(str[i])))||
			(base == 8 && str[i] >= '0' && str[i] < '8'))
			i++;
		else
			return (0);
	}
	return (1);
}
