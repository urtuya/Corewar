#include "../inc/head.h"

int		reverse_negative(int negative, int size)
{
	int i;
	int tmp;

	i = 1;
	tmp = 0xff;
	negative -= 1;
	while (i < size)
	{
		tmp |= 0xff << (8 * i);
		i++;
	}
	return (negative ^ tmp);
}

int		bin2int(unsigned char *buf, int size)
{
	int	i;
	int	tmp;
	int ret;
	int	flag;

	i = 0;
	ret = 0;
	flag = 0;
	tmp = size * 8 - 8;
	while (i < size)
	{
		if (!i && buf[i] & (0x1 << 7))
			flag = 1;
		ret += buf[i] << tmp;
		tmp -= 8;
		i++;
	}
	if (flag)
	{
		// NEGATIVE NUMBER, NEEDS TO REVERSE, IT WASNT WORKING EITHER WAY
		// printf("WAS %x %d\n", ret, ret);
		ret = -reverse_negative(ret, size);
		// printf("BECAME %x %d\n", ret, ret);
	}
	return (ret);
}

void	bin2str(int fd, char *buf, int len)
{
	int		size;

	size = read(fd, buf, len);
	if (size < 0)
		error("Error reading file\n", "");
	if (size != len)
		error("Invalid file\n", "");
}

void	champ_name(int fd, t_champ *champ)
{
	int size;

	size = read(fd, champ->header.prog_name, PROG_NAME_LENGTH);
	if (size < 0)
		error("Error reading file\n", "");
	if (size != PROG_NAME_LENGTH)
		error("Invalid file\n", "");
}

int		read_bin(int fd, int len)
{
	int size;
	unsigned char buf[4];

	size = read(fd, &buf, len);
	if (size < 0)
		error("Error reading file\n", "");
	if (size != len)
		error("Invalid file\n", "");
	return (bin2int(buf, len));
}

unsigned char	*read_code(int fd, int len)
{
	unsigned char	*buf;
	unsigned char	end_of_file;
	int				size;

	malloc_err((buf = (unsigned char*)malloc(sizeof(unsigned char) * len)), "read_code in main()");
	size = read(fd, buf, len);
	if (size < 0)
		error("Error reading file\n", "");
	if (size < len)
		error("Invalid file\n", "");
	if (read(fd, &end_of_file, 1) != 0)
		error("Invalid file\n", "");
	return (buf);
}

void	check_valid(char *file, t_champ *champ)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error("Error open file: %s\n", file);
	champ->header.magic = read_bin(fd, MAGIC_HEADER_SIZE);
	if (champ->header.magic != COREWAR_EXEC_MAGIC)
		error("Magic header: %s\n", file);
	bin2str(fd, champ->header.prog_name, PROG_NAME_LENGTH);
	if (read_bin(fd, NULL_SIZE) != 0)
		error("No NULL after champion: %s\n", file);
	champ->header.prog_size = read_bin(fd, EXEC_CODE_SIZE);
	if (champ->header.prog_size > CHAMP_MAX_SIZE)
	{
		fprintf(stderr, "Error: File %s has too large a code (%d bytes > 682 bytes)\n", file, champ->header.prog_size);
		exit(1);
	}
	bin2str(fd, champ->header.comment, COMMENT_LENGTH);
	if (read_bin(fd, NULL_SIZE) != 0)
		error("No NULL after champion: %s\n", file);
	champ->exec_code = read_code(fd, champ->header.prog_size);
}
