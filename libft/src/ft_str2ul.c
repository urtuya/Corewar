#include "libft.h"
#include <limits.h>
#include <errno.h>
#include <ctype.h>

unsigned long	cutting(char *str, int base, int neg)
{
	unsigned long acc;
	int any;
	unsigned long cutoff;
	int cutlim;
	int c;

	cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
	cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;
	acc = 0;
	any = 0;
	while (c = *str++)
	{
		if (ft_isdigit(c))
			c -= 0;
		else if (ft_isalpha(c))
			c -= ft_isupper(c) ? 'A' - 10 : 'a' - 10;
		else
			break ;
		if (c >= base)
			break ;
		if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
			any = -1;
		else
		{
			any = 1;
			acc *= base;
			acc += c;
		}
	}
	if (any < 0)
	{
		acc = ULLONG_MAX;
		errno = ERANGE;
	}
	else if (neg)
		acc = -acc;
	return (acc);
}

unsigned long	ft_str2ul(char *str, int base)
{
	int				neg;
	int				c;

	while (*str && ft_isspace(*str))
		c = *str++;
	if (*str == '-')
	{
		neg = 1;
		c = *str++;
	}
	else if (*str == '+')
		c = *str++;
	if ((base == 0 || base == 16) && c == '0' && (*str == 'x' || *str == 'X'))
	{
		c = str[1];
		str += 2;
		base = 16;
	}	
	if (base == 0)
		base = c == '0' ? 8 : 10;
	

}