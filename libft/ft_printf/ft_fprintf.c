#include "ft_printf.h"

static int		get_stream(FILE *stream)
{
	if (stream == stdin)
		return (0);
	else if (stream == stdout)
		return (1);
	else
		return (2);
}

int				ft_fprintf(FILE *stream, const char *format, ...)
{
	int		ret;
	va_list	args;

	ret = 0;
	va_start(args, format);
	ret = ft_printf_(args, format, get_stream(stream));
	va_end(args);
	return (ret);
}