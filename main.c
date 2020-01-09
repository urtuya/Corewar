#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	bin_to_int(unsigned char *bin, int size)
{
	int		i;
	int		res;

	i = 1;
	res = 0;
	while (i <= size)
	{
		res += bin[i - 1] << ((size - i) * 8);
		// printf("res = %x\n", res);
		// printf("i = %d\n", i);
		i++;
	}
	return (res);
}

int bin2int(unsigned char *buf, int size)
{
	int i;
	int res;

	i = 0;
	res = 0; // all size is 4 bytes = 32 bits !!!!!!!
	// while (i < size)
	// {
	res = buf[i];
	printf("res = %x\n", res);
	res = buf[i + 1];
	printf("res = %x\n", res);
	res = buf[i + 2];
	printf("res = %x\n", res);
	res = buf[i + 3];
	printf("res = %x\n", res);
	// }
}

int main(int argc, char **argv)
{
	int				fd;
	int				size;
	unsigned char	buf[100];

	fd = open (argv[1], O_RDONLY);
	read (fd, &buf, 4);
	size = bin_to_int(buf, 4); //magic header 4 bytes 00ea83f3
	bin2int(buf, 4);
	printf("size = %d\n", size);

	return (0);
	
}