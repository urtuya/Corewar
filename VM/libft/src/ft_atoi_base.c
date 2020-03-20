#include "libft.h"
#include <stdint.h>

static int	get_base(char *str, int *base)
{
	int i;

	i = 0;
	if (str[i] == '0' && str[i + 1])
	{
		if (lower_upper(str[i + 1], 'x'))
		{
			*base = 16;
			i += 2;
		}
		else if (lower_upper(str[i + 1], 'b'))
		{
			*base = 2;
			i += 2;
		}
		else
		{
			*base = 8;
			i++;
		}
	}
	else if (str[i + 1])
		*base = 10;
	return (i);
}

static int	clear_spaces(char *str, intmax_t *sign, int *base)
{
	int i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		*sign = str[i] == '-' ? -1 : 1;
		i++;
	}
	i += get_base(str + i, base);
	return (i);
}

intmax_t	ft_atoi_base(char *str, int base)
{
	int			i;
	int			digit;
	intmax_t	sign;
	intmax_t	ret;

	if (!str || !*str)
		return (0);
	ret = 0;
	sign = 1;
	i = clear_spaces(str, &sign, &base);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			digit = str[i] - '0';
		else if (ft_isalpha(str[i]))
			digit = ft_isupper(str[i]) ? str[i] - 'A' + 10 : str[i] - 'a' + 10;
		else
			break ;
		if (digit >= base)
			break ;
		ret *= base;
		ret += digit;
		i++;
	}
	return (ret * sign);
}