#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	int fd;
	int size;
	int sizecounter;
	unsigned char *buf;
	char str[17] = "0123456789abcdef";

	buf = malloc(sizeof(unsigned char*) * 1000);

	sizecounter = 0;
	fd = open(argv[1], O_RDONLY);
	while ((size = read(fd, buf, 100)) > 0)
		sizecounter += size;
	printf("size = %d\n", sizecounter);
	printf ("buf = %c\n", str[buf[0]]);
	return (0);
}
