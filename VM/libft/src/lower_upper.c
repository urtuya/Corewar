#include "libft.h"

int	lower_upper(int c, int b)
{
	if (ft_isupper(b))
	{
		c = ft_toupper(c);
	}
	else if (ft_islower(b))
	{
		c = ft_tolower(c);
	}
	if (c == b)
		return (1);
	return (0);
}
